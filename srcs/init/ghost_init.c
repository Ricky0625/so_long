/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:40:18 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/28 18:25:00 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ghost_init(t_game *game, t_ghost *ghost)
{
	ghost->appear_counter = 0;
	anim_init(&ghost->idle, 10, game->img_db.ghost_idle);
}

void	add_ghost(t_game *game, int x, int y)
{
	t_ghost	*ghost;

	ghost = &game->ghost;
	ghost_init(game, ghost);
	ghost->loc.x = x;
	ghost->loc.y = y;
}
