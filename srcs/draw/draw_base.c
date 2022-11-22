/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:15:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 15:40:26 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Get the base images, specially for image that belongs to layer i.
 * 		  Check the definition of layer i at the comment of draw_base().
 */
t_image	*get_base_img(t_game *game, int x, int y)
{
	t_vector	size;

	size = game->map_data.size;
	if (x == 0 && y == 0)
		return (game->img_db.corner_up_left);
	else if (x == 0 && y == size.x - 1)
		return (game->img_db.corner_up_right);
	else if (x == size.y - 1 && y == 0)
		return (game->img_db.corner_down_left);
	else if (x == size.y - 1 && y == size.x - 1)
		return (game->img_db.corner_down_right);
	else if (x == 0 && (y > 0 && y < size.x - 1))
		return (game->img_db.side_up);
	else if (y == 0 && (x > 0 && x < size.y - 1))
		return (game->img_db.side_left);
	else if (y == size.x - 1 && (x > 0 && x < size.y - 1))
		return (game->img_db.side_right);
	else if (x == size.y - 1 && (y > 0 && y < size.x - 1))
		return (game->img_db.side_down);
	return (game->img_db.floor);
}

/**
 * @brief Set the starting pixel of each tile
 * 
 * For small map, the map will be placed at the center of the window. Before
 * this, the starting pixel has already been calculated. But, this starting
 * pixel is only the on screen position of the first tile (0, 0). In order
 * to draw the other tile on the precise precision, the on screen position
 * of that tile will be:
 * (index * sprite size) + starting pixel
 * 
 * For big map, the map will not be placed at the center of the window, so
 * the formula will be slightly different. As mentioned, big map will not
 * fit in a window so its index number * sprite size may potentially exceed
 * the screen size and when we try to draw it, it will cause segfault. To
 * deal with this and make sure that the images are draw on the correct
 * position, the index needs to deduct the start_index first. So this is
 * the formula:
 * (index - start_index) * sprite size + starting pixel
 */
void	set_tile_start_pixel(t_game *game, t_vector *pos, t_vector index)
{
	if (game->final.is_big == 0)
	{
		set_vector(pos,
			(index.y * SPT_SIZE) + pos->x,
			(index.x * SPT_SIZE) + pos->y);
	}
	else
	{
		set_vector(pos,
			(index.y - game->final.start_index.y) * SPT_SIZE + pos->x,
			(index.x - game->final.start_index.x) * SPT_SIZE + pos->y);
	}
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
 * @brief Draw the base of the map. Basically anything that are static, will not
 * 		  move when the game is running. This includes the floor, block, & the 
 * 		  wall (except vertical wall).
 * 		  Base consists of two layer:
 *        i.	The wall and floor (below)
 *        ii.	Block (above, overlay)
 * 		  Layer (i) will be drawn onto the screen first then the blocks.
 * 		  There's a special checking condition. If the character is a vertical
 *   	  wall ('V'), skip this. The reason is that, if i don't do that, the
 * 		  location of that vertical wall will be replaced by the floor. After
 * 		  that when drawing the vertical wall, we will replace the whole image
 * 		  to vertical wall again. So, the drawing here is unecessary.
 */
void	draw_base(t_game *game, t_vector index)
{
	char		**map;
	t_image		*base;
	t_vector	pos;
	t_vector	map_size;

	map = game->map_data.map;
	if (map[index.x][index.y] == 'V')
		return ;
	pos = game->final.start_pixel;
	map_size = game->map_data.size;
	set_tile_start_pixel(game, &pos, index);
	base = get_base_img(game, index.x, index.y);
	copy_image(base, game->final.img, pos.x, pos.y);
	if ((index.x > 0 && index.x < map_size.y - 1)
		&& (index.y > 0 && index.y < map_size.x - 1)
		&& map[index.x][index.y] == '1')
	{
		base = game->img_db.block;
		copy_image(base, game->final.img, pos.x, pos.y);
	}
}

/**
 * @brief Helper function to iterate through the map and run (draw *) on
 * 		  each of the character.
 */
void	mapiteri(t_game *game, void (*draw)(t_game *, t_vector))
{
	int			ori_start_y;
	t_vector	start;
	t_vector	end;

	start = game->final.start_index;
	end = game->final.end_index;
	ori_start_y = start.y;
	while (start.x <= end.x)
	{
		start.y = ori_start_y;
		while (start.y <= end.y)
		{
			draw(game, start);
			start.y++;
		}
		start.x++;
	}
}
