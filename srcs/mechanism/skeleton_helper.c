/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:41:02 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 17:42:36 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Intialize the patrolling destination tile of the skeleton
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

/**
 * @brief Check if the skeleton can continue patrolling to the direction.
 */
int	can_continue_patrolling(t_game *game, t_skeleton *skely)
{
	t_vector	dest;

	dest = get_skely_dest(skely->loc, skely->dir);
	if (detect_collision(game, dest, SKELETON) == 1)
		return (0);
	return (1);
}
