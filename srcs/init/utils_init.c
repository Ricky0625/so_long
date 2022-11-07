/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:42:41 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 13:48:16 by wricky-t         ###   ########.fr       */
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
	anim->picker = 1;
	anim->frames = frames;
}

/**
 * @brief Initialize the map_data struct
 */
void	map_data_init(t_map *map_data)
{
	map_data->file = NULL;
	map_data->raw = NULL;
	map_data->map = NULL;
}
