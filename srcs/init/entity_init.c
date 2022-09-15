/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:26:00 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/15 17:33:29 by wricky-t         ###   ########.fr       */
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

void	skeleton_init(t_skeleton *ske)
{
	ske->collide = 0;
	tile_init(&ske->me);
	ske->idle1 = 0;
	ske->idle2 = 0;
	ske->killed = 0;
}

void	ghost_init(t_ghost *gho)
{
	gho->show = 0;
	tile_init(&gho->me);
	gho->idle1 = 0;
	gho->idle2 = 0;
	gho->invisible = 0;
	gho->appear = 0;
}

void	vwall_init(t_vwall *vwall)
{
	vector_init(&vwall->loc);
	vwall->idle1 = 0;
	vwall->idle2 = 0;
	vwall->idle3 = 0;
}

void	collectible_init(t_coll *coll)
{
	tile_init(&coll->me);
	coll->idle1 = 0;
	coll->idle2 = 0;
}
