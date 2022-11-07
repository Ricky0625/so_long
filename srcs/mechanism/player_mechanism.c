/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanism.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:03:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 18:04:26 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Activate the ghost's skill (kill all the skeletons)
 * 
 * 1. If appear counter is greater than 0 OR there's no skeleton, don't run
 *    the function
 * 2. If the condition above cannot satisfy (meaning appear counter == 0 &&
 *    there is a skeleton)
 * 3. Set the skeleton's frame to skeleton_scared
 * 
 * Actually this only change the frame set of the skeletons
 */
void	ghost_boo(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	skeletons = game->skeletons;
	if (game->ghost.appear_counter > 0 || game->entity.skely == 0)
		return ;
	game->ghost.activate = 1;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		skely->anim.frames = game->img_db.skeleton_scared;
		skeletons = skeletons->next;
	}
}

/**
 * @brief Listen to input and move the player accordingly
 * 
 * W  : UP
 * A  : LEFT
 * S  : DOWN
 * D  : RIGHT
 * SP : Activate ghost
 * 
 * Before moving the player, check if the player move to the destination will
 * cause collision or not. If not, set the player's location to the destination.
 * Increment the move count as well.
 */
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
	else if (key == KEY_SP && game->ghost.activate == 0)
		ghost_boo(game);
	if (detect_collision(game, dest, PLAYER) == 0 && key != KEY_SP)
	{
		set_vector(&game->player.loc, dest.x, dest.y);
		game->player.moves++;
	}
}
