/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanism.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:03:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/25 17:52:14 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	collect_key(t_game *game, t_vector loc)
{
	t_list	*collectibles;
	t_coll	*coll;

	collectibles = game->collectibles;
	while (collectibles != NULL)
	{
		coll = collectibles->content;
		if (coll->loc.x == loc.x && coll->loc.y == loc.y
			&& coll->collected == 0)
		{
			coll->collected = 1;
			game->player.collected++;
		}
		collectibles = collectibles->next;
	}
}

int	is_collision(t_game *game, t_vector *ply_loc, t_vector dest)
{
	char	**map;

	map = game->map_data.map;
	set_vector(&dest, dest.x + ply_loc->x, dest.y + ply_loc->y);
	if (map[dest.x][dest.y] == '1' || map[dest.x][dest.y] == 'V')
		return (1);
	if (map[dest.x][dest.y] == 'G')
	{
		if (game->ghost.appear_counter > 0)
			game->ghost.appear_counter--;
	}
	if (map[dest.x][dest.y] == 'C')
		collect_key(game, dest);
	if (map[dest.x][dest.y] == 'E')
	{
		if (game->player.collected == game->entity.coll)
		{
			// exit game and free here
			printf("You won!\n");
			exit(0);
		}
	}
	return (0);
}

void	move_player(t_game *game, int key)
{
	t_vector	*ply_loc;
	t_vector	dest;

	ply_loc = &game->player.loc;
	vector_init(&dest);
	if (key == KEY_W)
		dest.x--;
	else if (key == KEY_A)
	{
		game->player.anim.frames = game->img_db.player_idle_l;
		dest.y--;
	}
	else if (key == KEY_S)
		dest.x++;
	else if (key == KEY_D)
	{
		game->player.anim.frames = game->img_db.player_idle_r;	
		dest.y++;
	}
	else if (key == KEY_SP && game->ghost.appear_counter == 0) // also need to check if player is beside it, UDLR
		game->ghost.activate = 1;
	if (is_collision(game, ply_loc, dest) == 0)
	{
		set_vector(ply_loc, ply_loc->x + dest.x, ply_loc->y + dest.y); // redundant
		game->player.moves++;
	}
}

/**
 * Ghost appear counter algo:
 * 
 * Version A
 * Number of skeleton / number of collectibles
 * If <= 0
 * 	higher appear counter (skeleton less than collectible)
 * 	number of collectibles * AC multiplier
 * else
 * 	lower appear counter (skeleton more than collectible)
 * 	number of collectibles * (AC multiplier)
 * 
 * 5 SKELY, 12 COLL
 * = 12 * 2 = 24
 * 
 * 12 SKELY, 5 COLL
 * = 5 * 2 = 10
 */
