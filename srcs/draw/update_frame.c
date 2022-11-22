/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:54:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 14:27:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Update the animation frame
 * 
 * Idea:
 * The animation frames are stored as an array of void pointers ending with
 * a NULL. There's a animation duration for each of the entity. The duration
 * here refers to the number of iteration of mlx_loop because this will be
 * executed inside that. There's also a int variable, current_tick that keep
 * track how many iteration has done.
 * Every time this function get called, it will increment the current_tick
 * and if the current tick is equal to animation duration, it means it's time
 * to change to another frame, by incrementing the current_frame. So that
 * during draw_map, the draw function can fetch the expected frame and draw
 * to the map image. Oh ya, also reset current_tick to 0, so that we can
 * continue to track when is the next time to change frame.
 */
void	update_frame(t_anim *anim)
{
	t_image	**frames;

	frames = anim->frames;
	anim->current_tick++;
	if (anim->current_tick == anim->duration)
	{
		anim->current_frame += anim->picker;
		if (frames[anim->current_frame] == NULL)
		{
			anim->current_frame--;
			anim->picker = -1;
		}
		if (anim->current_frame == 0 && anim->picker == -1)
			anim->picker = 1;
		anim->current_tick = 0;
	}
}

/**
 * @brief To update the animation frame of a list.
 * 
 * Trying to implement a generic function here. So depending on the types
 * of the entity, the content of the linked list will be typecasted to
 * the it's type. And then just update the frame.
 */
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

/**
 * @brief The main driver function to update the animation
 * 
 * There are some animation that I wanted it to be played once (one full cycle)
 * like the ghost activation, and exit animation. So, I just set it to if their
 * current frame is more than the total frames of the animtion, stop update.
 */
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
