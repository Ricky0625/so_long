/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:17:59 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 19:07:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize the tile
**/
void	tile_init(t_tile *tile)
{
	vector_init(&tile->loc);
	tile->type = 0;
}

/**
 * Initialize the player
**/
void	player_init(t_game *game)
{
	t_player *ply;

	ply = &game->player;
	find_entity(ply->player.loc);
	ply->player.type = 'P';
	tile_init(&ply->up);
	tile_init(&ply->down);
	tile_init(&ply->left);
	tile_init(&ply->right);
	ply->collected = 0;
	ply->move_count = 0;
}

/**
 * Get the surrounding tile of the player
**/
void	get_surrounding(t_player *player, char **map)
{
	int	x;
	int	y;

	x = player->player.loc.x;
	y = player->player.loc.y;
	player->up.type = map[x - 1][y];
	set_vector(player->up.loc, x - 1, y);
	player->down.type = map[x + 1][y];
	set_vector(player->down.loc, x + 1, y);
	player->left.type = map[x][y - 1];
	set_vector(player->left.loc, x, y - 1);
	player->right.type = map[x][y + 1];
	set_vector(player->right.loc, x, y + 1);
}

/**
 * Update player after initialize (if needed)
**/
void	player_update(t_player *player, char **map)
{
	get_surrounding(player, map);	
}
