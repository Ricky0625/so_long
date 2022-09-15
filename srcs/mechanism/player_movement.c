/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:52:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 19:21:18 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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

void	wipe_tile(t_tile *a, t_tile *b, char **map)
{
	char	*tile_a;
	char	*tile_b;

	tile_a = &map[a->loc.x][a->loc.y];
	tile_b = &map[b->loc.x][b->loc.y];
	*tile_b = a->type;
	*tile_a = '0';
}

/**
 * Restore previous tile if player is leaving 'exit' or 'ghost'
**/
void	restore_previous_tile(t_tile *a, t_tile *b, char prev_tile, char **map)
{
	char	*next;
	char	*prev;

	next = &map[b->loc.x][b->loc.y];
	prev = &map[a->loc.x][a->loc.y];
	*next = 'P';
	*prev = prev_tile;
}

/**
 * Move player around the map
**/
void	move_player(t_player *ply, t_tile *dest, char **map)
{
	char		tile;
	static char	prev_tile = '0';

	tile = dest->type;
	if (prev_tile == 'E' && ply->player.type == 'T')
		restore_previous_tile(&ply->player, dest, prev_tile, map);
	else
	{
		if (tile == '0')
			swap_tile(&ply->player, dest, map);
		else if (tile == 'E')
			overlay_tile(&ply->player, dest, map);
		// else if (tile == 'C')
		// {
		// 	print_surrounding(ply);
		// 	printf("run this\n");
		// 	printf("before: %d\n", ply->collected);
		// 	ply->collected += 1;
		// 	printf("after: %d\n", ply->collected);
		// 	wipe_tile(&ply->player, dest, map);
		// }
	}
	prev_tile = tile;
}
