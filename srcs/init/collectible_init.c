/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:20:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/28 18:05:12 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	collectible_init(t_game *game, t_coll *coll)
{
	coll->collected = 0;
	anim_init(&coll->idle, 10, game->img_db.key_idle);
	anim_init(&coll->effect, 10, game->img_db.key_effect);
}

void	add_collectible(t_game *game, int x, int y)
{
	t_list	**colls;
	t_coll	*coll;

	colls = &game->collectibles;
	coll = malloc(sizeof(t_coll));
	collectible_init(game, coll);
	coll->loc.x = x;
	coll->loc.y = y;
	ft_lstadd_back(colls, ft_lstnew(coll));
}