/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_mechanism.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:50:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 17:41:37 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Let the skeleton to start patrolling
 *
 * 1. Check if the skeleton's current tick is equal cooldown or not
 * 	  if it's not, meaning it's not now
 * 2. Calculate where the skeleton will be after patrolling
 * 3. Base on the output of step2, check if the skeleton will have
 *    a collsion if it move to that tile. But the return value
 *    of detect collision here is -1, which means it's checking if
 *    skeleton move to the desired tile, will it touch the player.
 *   If that's the case, exit program, the player lose.
 */
void	start_patrolling(t_game *game, t_skeleton *skely)
{
	t_vector	dest;

	if (skely->current_tick != PATROL_COOLDOWN)
		return ;
	dest = get_skely_dest(skely->loc, skely->dir);
	if (detect_collision(game, dest, SKELETON) == -1)
		exit_game(game, NULL, LOSE);
	if (skely->dir == RIGHT)
		skely->anim.frames = game->img_db.skeleton_idle_r;
	if (skely->dir == LEFT)
		skely->anim.frames = game->img_db.skeleton_idle_l;
	set_vector(&skely->loc, dest.x, dest.y);
}

/**
 * @brief Set the array skeleton of patrol direction
 * 
 * Check if UP, DOWN, LEFT, RIGHT of the skeleton will cause any collision
 * If YES, set to 0 (meaning cannot go to this tile)
 * If NO, set to 1 (meaning can go to this tile)
 * 
 * Iterate through the array direction, and check which direction can be used.
 * Extra condition is that, must not be the direction that the skeleton already
 * travelled to before. So that this will prevent the skeleton to move UP & DOWN
 * or LEFT & RIGHT only. If there's one direction that satisfy the condition,
 * set the patrolling direction to that direction.
 */
void	set_patrolling_direction(t_game *game, t_skeleton *skely)
{
	int			dir;
	t_vector	dest;
	t_vector	skely_loc;

	dir = -1;
	skely_loc = skely->loc;
	while (++dir < MAX_DIRECTION)
	{
		dest = get_skely_dest(skely_loc, dir);
		if (detect_collision(game, dest, SKELETON) == 1)
			skely->surrounding[dir] = 0;
		else
			skely->surrounding[dir] = 1;
	}
	dir = -1;
	while (++dir < MAX_DIRECTION)
	{
		if (skely->surrounding[dir] == 1 && skely->dir != (t_direction)dir)
		{
			skely->dir = (t_direction)dir;
			break ;
		}
	}
}

/**
 * @brief Set the patrolling direction of the skeleton
 *
 * 1. If the skeleton patrol direction is unset, set patrolling direction
 * 2. If the current tick of the skeleton (not animation) is less than the
 * 	  patrol cooldown, increment current tick and exit this function.
 * 3. If the current tick equal to the patrol cooldown, set patrolling data
 *    and reset the current tick to 0.
 */
void	set_patrol_data(t_game *game, t_skeleton *skely)
{
	if (skely->dir == UNSET)
		set_patrolling_direction(game, skely);
	if (skely->current_tick < PATROL_COOLDOWN)
	{
		skely->current_tick++;
		return ;
	}
	if (skely->current_tick == PATROL_COOLDOWN
		&& can_continue_patrolling(game, skely) == 0)
		set_patrolling_direction(game, skely);
	skely->current_tick = 0;
}

/**
 * @brief Check if the skeletons are dead
 *
 * 1. Only run this function if ghost has been activated and
 * 	  there's no skeleton
 * 2. If the case above does not apply (meaning ghost has been
 *    activated), check all the skeletons's animation current
 *    frame. If it's 6, meaning the last frame (hard coded ik)
 *    then delete all the node. Basically free the skeletons
 *    list.
 */
void	check_if_skeletons_dead(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	if (game->ghost.activate == 0 || game->skeletons == NULL)
		return ;
	skeletons = game->skeletons;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		if (skely->anim.current_frame == 6)
		{
			ft_lstdelall(game->skeletons);
			game->skeletons = NULL;
			break ;
		}
		skeletons = skeletons->next;
	}
}

/**
 * @brief The main driver function that control the skeleton patrol
 *
 * 1. If skeletons is null OR ghost is not activated yet, exit this function
 * 2. Iterate through the skeleton list and set patrol data for each skeleton.
 * 3. After the patrol data has been set, start patrolling.
 */
void	skeleton_patrol(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	skeletons = game->skeletons;
	if (skeletons == NULL || game->ghost.activate == 1)
		return ;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		set_patrol_data(game, skely);
		start_patrolling(game, skely);
		skeletons = skeletons->next;
	}
}
