/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vwall_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:03:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 14:10:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	vwall_init(t_game *game, t_vwall *vwall)
{
	anim_init(&vwall->anim, 10, game->img_db.vwall_idle);
	vector_init(&vwall->loc);
}

void	add_vwall(t_game *game, int x, int y)
{
	t_list	**vwalls;
	t_vwall	*vwall;

	vwalls = &game->vwalls;
	vwall = malloc(sizeof(t_vwall));
	vwall_init(game, vwall);
	vwall->loc.x = x;
	vwall->loc.y = y;
	ft_lstadd_back(vwalls, ft_lstnew(vwall));
}
