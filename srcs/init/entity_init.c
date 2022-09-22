/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:26:00 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/22 10:57:29 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize entity struct
**/
void	entity_init(t_entity *entity)
{
	entity->plyr = 0;
	entity->coll = 0;
	entity->exit = 0;
	entity->skely = 0;
	entity->ghost = 0;
}

/**
 * Initialize vertical wall (Decoration)
**/
void	vwall_init(t_vwall *vwall)
{
	vwall->me = NULL;
	vwall->idle1 = 0;
	vwall->idle2 = 0;
	vwall->idle3 = 0;
}

static void	get_vwall_list(t_game *game)
{
	t_tile	**tilemap;
	t_tile	*tile;
	t_vwall	*vwall;

	tilemap = game->tilemap;
	vwall = game->vwall;
	if (vwall == NULL)
		return ;
	while (*tilemap != NULL)
	{
		tile = *tilemap;
		while (tile->type != 0)
		{
			if (tile->type == VWALL)
			{
				vwall_init(vwall);
				vwall->me = tile;
				vwall++;
			}
			tile++;
		}
		tilemap++;
	}
	vwall->me = NULL;
}

void	vwall_update(t_game *game)
{
	int			num;

	num = game->map_data.size.x - 2;
	game->vwall = malloc(sizeof(t_vwall) * (num + 1));
	get_vwall_list(game);
}
