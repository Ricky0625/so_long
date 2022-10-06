/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:02:03 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/06 15:31:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	add_entity(t_game *game, t_enty_type type, t_vector loc)
{
	if (type == PLAYER)
		add_player(game, loc);
	else if (type == GHOST)
		add_ghost(game, loc);
	else if (type == SKELETON)
		add_skeleton(game, loc);
	else if (type == COLLECTIBLE)
		add_collectible(game, loc);
	else if (type == VWALL)
		add_vwall(game, loc);
}

void	update_entity(t_game *game)
{
	t_vector	loc;
	char		entity;
	char		**map;

	loc.x = -1;
	map = game->map_data.map;
	while (map[++loc.x] != NULL)
	{
		loc.y = -1;
		while (map[loc.x][++loc.y] != '\0')
		{
			entity = map[loc.x][loc.y];
			add_entity(game, entity, loc);
		}
	}
}
