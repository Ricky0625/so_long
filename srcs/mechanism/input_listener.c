/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:45:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 19:15:06 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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
		printf("W\n");
	else if (keycode == KEY_A)
		printf("A\n");
	else if (keycode == KEY_S)
		printf("S\n");
	else if (keycode == KEY_D)
		printf("D\n");
	return (0);
}
