/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:54:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 18:09:09 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void update_frame(t_anim *anim)
{
	t_image **frames;

	frames = anim->frames;
	anim->current_tick++;
	if (anim->current_tick == anim->duration)
	{
		anim->current_frame++;
		if (frames[anim->current_frame] == 0)
			anim->current_frame = 0;
		anim->current_tick = 0;
	}
}

void update_vwall_frame(void *content)
{
	t_vwall *vwall;

	vwall = content;
	update_frame(&vwall->anim);
}

void update_coll_frame(void *content)
{
	t_coll *coll;

	coll = content;
	update_frame(&coll->anim);
}

void update_skeleton_frame(void *content)
{
	t_skeleton *skely;

	skely = content;
	update_frame(&skely->anim);
}

void update_animation(t_game *game)
{
	update_frame(&game->player.anim);
	update_frame(&game->ghost.anim);
	ft_lstiter(game->vwalls, update_vwall_frame);
	ft_lstiter(game->collectibles, update_coll_frame);
	ft_lstiter(game->skeletons, update_skeleton_frame);
}