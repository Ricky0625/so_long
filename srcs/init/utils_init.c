/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:42:41 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/26 12:23:10 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	entity_init(t_entity *enty)
{
	enty->plyr = 0;
	enty->ghost = 0;
	enty->skely = 0;
	enty->coll = 0;
	enty->exit = 0;
}

void	anim_init(t_anim *anim, int duration, t_image **frames)
{
	anim->current_tick = 0;
	anim->duration = duration;
	anim->current_frame = 0;
	anim->frames = frames;
}

void	vector_init(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

void	set_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

int	is_same_vector(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y);
}
