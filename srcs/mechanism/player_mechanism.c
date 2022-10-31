/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanism.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:03:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/31 12:14:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ghost_boo(t_game *game)
{
	t_list		*skeletons;
	// t_skeleton	*skely;

	skeletons = game->skeletons;
	if (game->ghost.appear_counter > 0 || game->entity.skely == 0)
		return ;
	game->ghost.activate = 1;
	// just free it here (Skeletons)
	game->skeletons = NULL;
	// while (skeletons != NULL)
	// {
	// 	skely = skeletons->content;
	// 	if (skely->killed == 0)
	// 		skely->killed = 1;
	// 	skeletons = skeletons->next;
	// }
}

void	move_player(t_game *game, int key)
{
	t_vector	dest;

	set_vector(&dest, game->player.loc.x, game->player.loc.y);
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
	else if (key == KEY_SP)
		ghost_boo(game);
	if (detect_collision(game, dest, PLAYER) == 0)
	{
		set_vector(&game->player.loc, dest.x, dest.y);
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
