/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:52:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 20:34:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Check if the tile can be passed through
**/
int	can_pass_through(char tile_ch)
{
	return (tile_ch == '0' || tile_ch == 'E' || tile_ch == 'C'
		|| tile_ch == 'G');
}

void	swap_tile(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * Move player around the map
**/
void	move_player(t_tile *player, t_tile *dest, char **map)
{
	char	tile;

	tile = dest->type;
	if (tile == '0')
	{}
}
