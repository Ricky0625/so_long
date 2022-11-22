/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 16:55:36 by wricky-t         ###   ########.fr       */
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

void	calibrate_pixel_index(t_game *game)
{
	while (game->final.start_index.y < 0)
	{
		game->final.start_index.y++;
		game->final.start_pixel.x += SPT_SIZE;
	}
	while (game->final.start_index.x < 0)
	{
		game->final.start_index.x++;
		game->final.start_pixel.y += SPT_SIZE;
	}
	if (game->final.end_index.x > game->map_data.size.y - 1)
		game->final.end_index.x = game->map_data.size.y - 1;
	if (game->final.end_index.y > game->map_data.size.x - 1)
		game->final.end_index.y = game->map_data.size.x - 1;
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
	calibrate_pixel_index(game);
	mapiteri(game, draw_base);
	draw_entity(game);
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
