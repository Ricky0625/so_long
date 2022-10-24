/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:31:14 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/21 21:12:13 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	place_sprite(t_tile *tile, t_game *game)
{
	t_tiletype type;

	type = tile->type;
	if (type == WALL)
		place_wall_sprite(tile, game);
}

void	render(t_game *game)
{
	t_tile	*tile;
	t_tile	**tilemap;

	mlx_clear_window(game->ref, game->window.ref);
	tilemap = game->tilemap;
	while (*tilemap != 0)
	{
		tile = *tilemap;
		while (tile->type != 0)
		{
			place_sprite(tile, game);
			tile++;
		}
		tilemap++;
	}
}
