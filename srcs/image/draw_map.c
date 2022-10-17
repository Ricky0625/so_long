/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 21:58:32 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	draw_map(t_game *game)
{
	t_vector	size;

	size = game->map_data.size;
	set_vector(&size, size.x * SPT_SIZE, size.y * SPT_SIZE);
	game->map_img = new_image(game, size, 1);
	mapiteri(game, draw_base);
	draw_entity(game);
	get_final_map_img(game);
}

int	is_big_map(t_game *game)
{
	t_vector	map_size;

	map_size = game->map_data.size;
	set_vector(&map_size, map_size.x * 128, map_size.y *128);
	return (map_size.x >= WIN_HEIGHT && map_size.y >= WIN_HEIGHT);
}

/**
 * To get the final map:
 * 
 * 1. initialize the final map using new_image function. size is window size.
 * 2. Get the position of the player
 * 
 * @test print the map, if the index is negative, print space, print character
 * otherwise.
 * 
 * final img will always be placed at (0,0)
 */
void	get_final_map_img(t_game *game)
{
	t_final_img	*final_img;
	t_vector	map_size;
	
	final_img = &game->final_img;
	map_size = game->map_data.size;
	set_vector(&map_size, map_size.x * SPT_SIZE, map_size.y * SPT_SIZE);
	vector_init(&final_img->position);
	if (is_big_map(game) == 1)
	{
		
	}
	else
	{
		final_img->img = game->map_img;
		set_vector(&final_img->position, (WIN_WIDTH - map_size.x) / 2,
			(WIN_HEIGHT - map_size.y) / 2);
	}
}
