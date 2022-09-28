/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:49:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/28 18:40:37 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	skeleton_init(t_game *game, t_skeleton *skeleton)
{
	skeleton->collide = 0;
	anim_init(&skeleton->idle, 10, game->img_db.skeleton_idle);
	// anim_init(&skeleton->killed, 10, game->img_db.skeleton_killed);
}

void	add_skeleton(t_game *game, int x, int y)
{
	t_list		**skeletons;
	t_skeleton	*skely;

	skeletons = &game->skeletons;
	skely = malloc(sizeof(t_skeleton));
	skeleton_init(game, skely);
	skely->loc.x = x;
	skely->loc.y = y;
	ft_lstadd_back(skeletons, ft_lstnew(skely));
}
