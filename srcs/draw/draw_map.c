/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/16 19:47:01 by wricky-t         ###   ########.fr       */
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

// copy from 0,0 to end of the map
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
 * @brief Draw the map based on the map
 */
void	draw_map(t_game *game)
{
	if (game->final.img != NULL)
		free_img(game->final.img);
	game->final.img = xpm_to_image(game, BG, 1);
	vector_init(&game->final.on_screen_pos);
	if (is_big_map(game) == 1)
	{
		/**
		 * IDEAS:
		 * 
		 * Start counting from the location of player, find the starting & ending index
		 * Based on starting and ending index, get the starting pixel (place the image at where?)
		 * Recalibrate, if there is anything that is negative or out of map.
		 * 
		 * Draw the base first, need to think how to use the is_in_range to see which base
		 * needs to be draw on the screen.
		 * Draw the entity afterward.
		 * 
		 * The memory part should already be handled by the small map. So, no worry I guess?
		 */
	}
	else
		draw_small(game);
	draw_ui(game);
}
