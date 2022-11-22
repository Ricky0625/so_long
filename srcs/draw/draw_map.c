/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 13:38:56 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if the map is a big map or not. The definition of big map
 * 		  here refers to the maps that are either:
 * 		  1. Horizontally & vertically
 * 		  2. Horizontally
 * 		  3. Vertically
 */
int	is_big_map(t_game *game)
{
	t_vector	map_size;

	map_size = game->map_data.size;
	set_vector(&map_size, map_size.x * SPT_SIZE, map_size.y * SPT_SIZE);
	return ((map_size.x > WIN_WIDTH && map_size.y > WIN_HEIGHT)
		|| (map_size.x > WIN_WIDTH && map_size.y <= WIN_HEIGHT)
		|| (map_size.x <= WIN_WIDTH && map_size.y > WIN_HEIGHT));
}

/**
 * Draw small map
 * 
 * @brief The procedure to draw small map. The start & end index will
 * 		  be set first. Start index will always be 0,0. For end index,
 * 		  it will always be the max height & max width of the map.
 * 		  Based on the start & end index, set the starting pixel
 * 		  (paste the image from what pixel).
 * 		  For small map, the formula to calculate the starting pixel is:
 * 		  x: [Window width - (map's width * Sprite size)] / 2
 * 		  y: [Window height - (map's height * Sprite size)] / 2
 * 		  After the starting pixel is set, draw the base and entity.
 */
void	draw_small(t_game *game)
{
	t_vector	*start;
	t_vector	*end;
	t_vector	*dst_pos;

	start = &game->final.start_index;
	end = &game->final.end_index;
	dst_pos = &game->final.start_pixel;
	vector_init(start);
	set_vector(end, game->map_data.size.y - 1, game-> map_data.size.x - 1);
	set_vector(dst_pos, (WIN_WIDTH - game->map_data.size.x * SPT_SIZE) / 2,
		(WIN_HEIGHT - game->map_data.size.y * SPT_SIZE) / 2);
	mapiteri(game, draw_base);
	draw_entity(game);
}

/**
 * Draw big map
 * 
 * @brief The procedure to draw big map. The start & end index must also be
 * 		  initialize before this function runs. Based on the start &
 * 		  end index, set the starting pixel (paste the image from what
 * 		  pixel). For small map, the formula to calculate the starting
 * 		  pixel is:
 * 		  x: [Window width - (map's width * Sprite size)] / 2
 * 		  y: [Window height - (map's height * Sprite size)] / 2
 * 		  After the starting pixel is set, draw the base and entity.
 */
void	draw_big(t_game *game)
{
	t_player	ply;
	t_vector	padding;

	ply = game->player;
	set_vector(&padding, ((WIN_HEIGHT / SPT_SIZE - 1) / 2),
		((WIN_WIDTH / SPT_SIZE - 1) / 2));
	set_vector(&game->final.start_index, ply.loc.x - padding.x,
		ply.loc.y - padding.y);
	set_vector(&game->final.end_index, ply.loc.x + padding.x,
		ply.loc.y + padding.y);
	vector_init(&game->final.start_pixel);
	if (game->final.start_index.y < 0)
	{
		game->final.start_pixel.x = ft_abs(game->final.start_index.y) * SPT_SIZE;
		game->final.start_index.y = 0;
	}
	if (game->final.start_index.y < 0)
	{
		game->final.start_pixel.y = ft_abs(game->final.start_index.x) * SPT_SIZE;
		game->final.start_index.x = 0;
	}
	if (game->final.end_index.x > game->map_data.size.y - 1)
		game->final.end_index.x = game->map_data.size.y - 1;
	if (game->final.end_index.y > game->map_data.size.x - 1)
		game->final.end_index.y = game->map_data.size.x - 1;
	mapiteri(game, draw_base);
	draw_entity(game);
}

/**
 * @brief Place the image of the numbers onto the screen
 * 
 * The numbers are stored in a array. Like 0 is at index 0, 1 at index 1, etc.
 * So, just itoa the player's moves count and iterate through the str.
 * For each character, minus it with '0' and we can get the index number.
 * Use that to access which image to display. After that just draw the number
 * onto the screen
 */
void	draw_ui(t_game *game)
{
	char		*str;
	char		*tmp;
	t_image		*num;
	int			loc_y;

	str = ft_itoa(game->player.moves);
	tmp = str;
	loc_y = 32;
	while (*str != '\0')
	{
		num = game->img_db.numbers[(*str - '0')];
		copy_image(num, game->final.img, loc_y, 32);
		loc_y += 64;
		str++;
	}
	free(tmp);
}

/**
 * @brief Draw the map based on the map
 * 
 * Since I'm using one pointer to store the address of the final img, before
 * creating a blank image to draw on, I need to free the previous pointer to
 * the final img first. After that, based on the size of the map (small / big),
 * draw the final img.
 * Small: The map can fit inside the window size
 * Big	: The map exceed the window size
 */
void	draw_map(t_game *game)
{
	if (game->final.img != NULL)
		free_img(game->final.img);
	game->final.img = xpm_to_image(game, BG, 1);
	vector_init(&game->final.on_screen_pos);
	if (is_big_map(game) == 1)
	{
		game->final.is_big = 1;
		draw_big(game);
	}
	else
	{
		game->final.is_big = 0;
		draw_small(game);
	}
	draw_ui(game);
}
