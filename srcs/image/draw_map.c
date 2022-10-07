/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/07 11:19:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	is_big_map(t_game *game)
{
	t_vector	size;

	size = game->map_data.size;
	size.x *= SPT_SIZE;
	size.y *= SPT_SIZE;
	return (size.x > WIN_WIDTH || size.y > WIN_HEIGHT);
}

void	get_start_end_point(t_vector ply_loc, t_vector *start, t_vector *end)
{
	int	width_ex;
	int	height_ex;

	width_ex = ((WIN_WIDTH / 128) - 1) / 2;
	height_ex = ((WIN_HEIGHT / 128) - 1) / 2;
	/**
	 * If any of the vector has negative value
	 * OR
	 * exceed the width or height of the map
	 */
	printf("we: %d, he: %d\n", width_ex, height_ex);
	printf("player: %d %d\n", ply_loc.x, ply_loc.y);
	printf("start: %d %d\n", ply_loc.x - height_ex, ply_loc.y - width_ex);
	printf("end: %d %d\n", ply_loc.x + height_ex, ply_loc.y + width_ex);
	(void)ply_loc;
	(void)start;
	(void)end;
}

void	get_map_fraction(t_game *game, t_vector *start, t_vector *end)
{
	t_vector	size;
	t_vector	player_loc;

	player_loc = game->player.loc;
	if (is_big_map(game) == 1)
	{
		set_vector(&size, WIN_WIDTH, WIN_HEIGHT);
		game->map_img = new_image(game, size, 1);
		get_start_end_point(player_loc, start, end);
	}
	else
	{
		set_vector(&size, game->map_data.size.x * SPT_SIZE,
			game->map_data.size.y * SPT_SIZE);
		game->map_img = new_image(game, size, 1);
		set_vector(start, 0, 0);
		set_vector(end, game->map_data.size.x - 1, game->map_data.size.y - 1);
	}
}

void	draw_map(t_game *game)
{
	t_vector	start;
	t_vector	end;

	get_map_fraction(game, &start, &end);
	/**
	 * @todo draw base function should takes in game struct and two vector.
	 * That two vectors will indicate the start loc and end loc of the map to copy.
	 * 
	 * @todo draw entity function should also do the same thing
	 * 
	 * Dear future me, this solution is to avoid create a copy of the map.
	 */
	draw_base(game);
	draw_entity(game);
}
