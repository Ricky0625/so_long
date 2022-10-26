/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_mechanism.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:50:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/25 19:32:42 by wricky-t         ###   ########.fr       */
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

void	is_collision_skely(t_direction direction, t_vector skely_loc)
{
	t_vector	dest;

	set_vector(&dest, skely_loc.x, skely_loc.y);
	if (direction == UP)
		dest.x--;
	else if (direction == DOWN)
		dest.x++;
	else if (direction == LEFT)
		dest.y--;
	else if (direction == RIGHT)
		dest.y++;
}

t_direction	get_roaming_direction()
{
	int	direction;

	direction = rand() % 4;
	return (direction);
}

void	skeleton_roaming(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;
	t_direction	direction;

	skeletons = game->skeletons;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		direction = get_roaming_direction();
		is_collision_skely(direction, skely->loc);
		skeletons = skeletons->next;
	}
}
