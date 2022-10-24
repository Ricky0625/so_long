/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:06:29 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/20 17:24:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Basically a strchr but instead of searching for a character in a string,
 * search for a tile in a tilemap
**/
t_tile	*tilechr(t_tile *tile, t_tiletype type)
{
	while (tile->type != 0)
	{
		if (tile->type == type)
			return (tile);
		tile++;
	}
	return (0);
}

void	tileiteri(t_game *game, void (*f)(t_game *, int, int))
{
	t_tile		**tilemap;
	t_tile		*tile;
	t_vector	index;

	tilemap = game->tilemap;
	vector_init(&index);
	while (*tilemap != NULL)
	{
		tile = *tilemap;
		index.y = 0;
		while (tile->type != 0)
		{
			f(game, index.x, index.y);
			index.y++;
			tile++;
		}
		index.x++;
		tilemap++;
	}
}
