/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_mechanism.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:50:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/31 15:57:39 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Idea:
 * 
 * 1. Generate a random number between 1 to 4.
 * 		a. 1 = U
 * 		b. 2 = D
 * 		c. 3 = L
 * 		d. 4 = R
 * 	  // use enum might be more clean
 * 2. Move
 * 		a. before move, check if there's a collision
 * 			i. if no, move
 * 			ii. yes, go step 1 again.
 * 
 * Entity/object that will cause collision
 * a. Ghost (back to step 1)
 * b. Wall (back to step 1)
 * c. player (end game)
 * 
 * Skeleton can overlap each other (skeleton-right animation maybe?)
 */

t_vector	get_skely_dest(t_vector ori, int dir)
{
	t_vector	dest;

	set_vector(&dest, ori.x, ori.y);
	if (dir == UP)
		dest.x--;
	else if (dir == DOWN)
		dest.x++;
	else if (dir == LEFT)
		dest.y--;
	else if (dir == RIGHT)
		dest.y++;
	return (dest);
}

void	start_roaming(t_game *game, t_skeleton *skely)
{
	t_vector	dest;

	if (skely->current_tick != ROAMING_COOLDOWN)
		return ;
	dest = get_skely_dest(skely->loc, skely->dir);
	if (detect_collision(game, dest, SKELETON) == -1)
		exit(0);
	set_vector(&skely->loc, dest.x, dest.y);
}

// set surrounding array and set the roaming direction
void	set_roaming_direction(t_game *game, t_skeleton *skely)
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

int	can_continue_roaming(t_game *game, t_skeleton *skely)
{
	t_vector	dest;

	dest = get_skely_dest(skely->loc, skely->dir);
	if (detect_collision(game, dest, SKELETON) == 1)
		return (0);
	return (1);
}

void	set_roaming_data(t_game *game, t_skeleton *skely)
{
	if (skely->dir == UNSET)
		set_roaming_direction(game, skely);
	if (skely->current_tick < ROAMING_COOLDOWN)
	{
		skely->current_tick++;
		return ;
	}
	if (skely->current_tick == ROAMING_COOLDOWN && can_continue_roaming(game, skely) == 0)
		set_roaming_direction(game, skely);
	skely->current_tick = 0;
}

void	skeleton_roaming(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	skeletons = game->skeletons;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		set_roaming_data(game, skely);
		start_roaming(game, skely);
		skeletons = skeletons->next;
	}
}
