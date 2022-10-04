/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:49:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 17:57:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	skeleton_init(t_game *game, t_skeleton *skeleton)
{
	skeleton->collide = 0;
	anim_init(&skeleton->anim, 10, game->img_db.skeleton_idle);
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
