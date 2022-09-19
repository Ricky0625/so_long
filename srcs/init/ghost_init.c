/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:28:56 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 17:24:32 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize ghost (not enemy)
**/
void	ghost_init(t_ghost *gho)
{
	gho->show = 0;
	gho->me = NULL;
	gho->idle1 = 0;
	gho->idle2 = 0;
	gho->invisible = 0;
	gho->appear = 0;
}

void	ghost_update(t_game *game)
{
	t_vector	loc;
	t_ghost		*ghost;

	if (game->entity.ghost == 0)
		return ;
	find_entity(&loc, game->map_data.map, 'G');
	ghost = &game->ghost;
	ghost->me = &game->tilemap[loc.x][loc.y];
}
