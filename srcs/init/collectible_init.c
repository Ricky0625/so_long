/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:16:00 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 20:20:48 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize collectibles
**/
void	collectible_init(t_coll *coll)
{
	coll->me = 0;
	coll->idle1 = 0;
	coll->idle2 = 0;
}

static void	get_collectible_list(t_game *game)
{
	t_tile	**tilemap;
	t_tile	*tile;
	t_coll	*coll;

	tilemap = game->tilemap;
	coll = game->collectibles;
	if (coll == NULL)
		return ;
	while (*tilemap != NULL)
	{
		tile = *tilemap;
		while (tile->type != 0)
		{
			if (tile->type == COLLECTIBLE)
			{
				collectible_init(coll);
				coll->me = tile;
				coll++;
			}
			tile++;
		}
		tilemap++;
	}
	coll->me = NULL;
}

void	collectible_update(t_game *game)
{
	int			num;

	num = game->entity.coll;
	if (num <= 0)
		return ;
	game->collectibles = malloc(sizeof(t_coll) * (num + 1));
	get_collectible_list(game);
}
