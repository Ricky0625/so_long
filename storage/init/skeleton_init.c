/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:43:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 19:48:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize skeleton (enemy)
**/
void	skeleton_init(t_skeleton *ske)
{
	ske->collide = 0;
	ske->me = NULL;
	ske->idle1 = 0;
	ske->idle2 = 0;
	ske->killed = 0;
}

static void	get_skeleton_list(t_game *game)
{
	t_tile		**tilemap;
	t_tile		*tile;
	t_skeleton	*skely;

	tilemap = game->tilemap;
	skely = game->skeleton;
	if (skely == NULL)
		return ;
	while (*tilemap != NULL)
	{
		tile = *tilemap;
		while (tile->type != 0)
		{
			if (tile->type == SKELETON)
			{
				skeleton_init(skely);
				skely->me = tile;
				skely++;
			}
			tile++;
		}
		tilemap++;
	}
	skely->me = NULL;
}

void	skeleton_update(t_game *game)
{
	int			num;

	num = game->entity.skely;
	if (num <= 0)
		return ;
	game->skeleton = malloc(sizeof(t_skeleton) * (num + 1));
	get_skeleton_list(game);
}
