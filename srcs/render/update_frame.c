/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:54:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/01 12:27:25 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	update_frame(t_anim *anim)
{
	t_image	**frames;

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

void	lst_update_frame(t_list *lst, t_enty_type type, void (*updt)(t_anim *))
{
	while (lst != NULL)
	{
		if (type == SKELETON)
			updt(&((t_skeleton *)lst->content)->anim);
		else if (type == COLLECTIBLE)
			updt(&((t_coll *)lst->content)->anim);
		else if (type == VWALL)
			updt(&((t_vwall *)lst->content)->anim);
		lst = lst->next;
	}
}

void	update_animation(t_game *game)
{
	update_frame(&game->player.anim);
	update_frame(&game->ghost.anim);
	if (game->ghost.activate == 1 && game->ghost.effect.current_frame < 4)
		update_frame(&game->ghost.effect);
	if (game->player.collected == game->entity.coll
		&& game->exit.anim.current_frame < 5)
		update_frame(&game->exit.anim);
	lst_update_frame(game->skeletons, SKELETON, update_frame);
	lst_update_frame(game->collectibles, COLLECTIBLE, update_frame);
	lst_update_frame(game->vwalls, VWALL, update_frame);
}
