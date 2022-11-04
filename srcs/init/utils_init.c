/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:42:41 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:36:27 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initialize the entity struct
 * 
 * This struct is used to record the numbers of each of the entity in the game
 */
void	entity_init(t_entity *enty)
{
	enty->plyr = 0;
	enty->ghost = 0;
	enty->skely = 0;
	enty->coll = 0;
	enty->exit = 0;
}

/**
 * @brief Initialize the animation struct
 */
void	anim_init(t_anim *anim, int duration, t_image **frames)
{
	anim->current_tick = 0;
	anim->duration = duration;
	anim->current_frame = 0;
	anim->frames = frames;
}

/**
 * @brief Initialize the vector
 */
void	vector_init(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

/**
 * @brief Set the vector based on the given input
 */
void	set_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

/**
 * @brief Check if two vector has the same value
 */
int	is_same_vector(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y);
}
