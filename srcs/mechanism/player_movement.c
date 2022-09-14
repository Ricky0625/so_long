/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:52:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 14:51:57 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Check if the tile can be passed through
**/
// int	can_pass_through(char tile_ch)
// {
// 	return (tile_ch == '0' || tile_ch == 'E' || tile_ch == 'C'
// 		|| tile_ch == 'G');
// }

void	swap_tile(t_tile *a, t_tile *b, char **map)
{
	char	*tile_a;
	char	*tile_b;
	char	temp;

	tile_a = &map[a->loc.x][a->loc.y];
	tile_b = &map[b->loc.x][b->loc.y];
	temp = *tile_b;
	*tile_b = *tile_a;
	*tile_a = temp;
}

void	overlay_tile(t_tile *a, t_tile *b, char **map)
{
	char	*tile_a;
	char	*tile_b;

	tile_a = &map[a->loc.x][a->loc.y];
	tile_b = &map[b->loc.x][b->loc.y];
	if (*tile_b == 'E')
		*tile_b = 'T';
	*tile_a = '0';
}

// void	restore_previous_tile(t_tile *ply, char prev_tile, char **map)
// {
	
// }

/**
 * Move player around the map
**/
void	move_player(t_tile *player, t_tile *dest, char **map)
{
	char		tile;
	static char	prev_tile = 0;

	if (prev_tile == 'E')
	{
		printf("last tile i stepped on is exit\n");
		return ;
	}
	tile = dest->type;
	prev_tile = tile;
	if (tile == '0')
		swap_tile(player, dest, map);
	else if (tile == 'E')
		overlay_tile(player, dest, map);
	show_path(map);
}
