/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:45:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 12:52:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	update_frame(t_game *game)
{
	place_map(game);
	return (0);
}

/**
 * Listen to the user input while the program is running
 * 
 * Control keys
 * Movement: WASD
**/
int	input_listener(int keycode, t_game *game)
{
	char		**map;
	t_player	*ply;

	map = game->map_data.map;
	ply = &game->player;
	if (keycode == KEY_W)
		move_player(&ply->player, &ply->up, map);
	else if (keycode == KEY_A)
		move_player(&ply->player, &ply->left, map);
	else if (keycode == KEY_S)
		move_player(&ply->player, &ply->down, map);
	else if (keycode == KEY_D)
		move_player(&ply->player, &ply->right, map);
	player_update(ply, map);
	return (0);
}
