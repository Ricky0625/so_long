/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:17:59 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/16 20:14:16 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Get the surrounding tile of the player
**/
// void	get_surrounding(t_player *player, char **map)
// {
// 	int	x;
// 	int	y;

// 	x = player->player.loc.x;
// 	y = player->player.loc.y;
// 	player->up.type = map[x - 1][y];
// 	set_vector(&player->up.loc, x - 1, y);
// 	player->down.type = map[x + 1][y];
// 	set_vector(&player->down.loc, x + 1, y);
// 	player->left.type = map[x][y - 1];
// 	set_vector(&player->left.loc, x, y - 1);
// 	player->right.type = map[x][y + 1];
// 	set_vector(&player->right.loc, x, y + 1);
// }

/**
 * Initialize the player
**/
void	player_init(t_player *player)
{
	player->moves = 0;
	player->collected = 0;
	player->me = NULL;
	player->idle1 = 0;
	player->idle2 = 0;
}

/**
 * Update player after initialize (if needed)
**/
void	player_update(t_game *game)
{
	t_vector	loc;
	t_player	*player;

	vector_init(&loc);
	find_entity(&loc, game->map_data.map, 'P');
	player = &game->player;
	player->me = &game->tilemap[loc.x][loc.y];
}

// void	print_surrounding(t_player *ply)
// {
// 	ft_printf("  %c\n", ply->up.type);
// 	ft_printf("%c %c %c\n", ply->left.type, ply->player.type, ply->right.type);
// 	ft_printf("  %c\n", ply->down.type);
// }
