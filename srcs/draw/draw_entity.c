/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:29:49 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 19:40:43 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if a set of index is within the range of two set of index
 */
int	is_in_range(t_vector start, t_vector end, t_vector index)
{
	return ((index.x >= start.x && index.x <= end.x)
		&& (index.y >= start.y && index.y <= end.y));
}

/**
 * @brief Draw the image to the final image
 */
void	draw_to_map(t_game *game, t_anim *anim, t_vector loc)
{
	t_image		*frame;
	t_vector	pos;

	if (is_in_range(game->final.start_index, game->final.end_index, loc) == 0)
		return ;
	frame = anim->frames[anim->current_frame];
	pos = game->final.start_pixel;
	if (game->final.is_big == 0)
		set_vector(&pos, (loc.y * SPT_SIZE) + pos.x,
			(loc.x * SPT_SIZE) + pos.y);
	else
	{
		set_vector(&pos, (loc.y - game->final.start_index.y) * SPT_SIZE + pos.x,
			(loc.x - game->final.start_index.x) * SPT_SIZE + pos.y);
	}
	copy_image(frame, game->final.img, pos.x, pos.y);
}

/**
 * @brief Draw the image of each node of a linked list to the screen
 */
void	lst_draw_frame(t_game *game, t_list *lst, t_enty_type type,
	void (*draw)(t_game *, t_anim *, t_vector loc))
{
	t_skeleton	*skely;
	t_coll		*coll;
	t_vwall		*vwall;

	while (lst != NULL)
	{
		if (type == SKELETON)
		{
			skely = lst->content;
			draw(game, &skely->anim, skely->loc);
		}
		else if (type == COLLECTIBLE)
		{
			coll = lst->content;
			draw(game, &coll->anim, coll->loc);
		}
		else if (type == VWALL)
		{
			vwall = lst->content;
			draw(game, &vwall->anim, vwall->loc);
		}
		lst = lst->next;
	}
}

/**
 * @brief Draw all the entity onto the map image
 * 
 * 1. For ghost, only draw it if there's a ghost, and appear counter
 *    is 0, and there is enemy
 * 2. For ghost activation effect, only draw if ghost is activated.
 */
void	draw_entity(t_game *game)
{
	lst_draw_frame(game, game->skeletons, SKELETON, draw_to_map);
	lst_draw_frame(game, game->collectibles, COLLECTIBLE, draw_to_map);
	lst_draw_frame(game, game->vwalls, VWALL, draw_to_map);
	draw_to_map(game, &game->exit.anim, game->exit.loc);
	draw_to_map(game, &game->player.anim, game->player.loc);
	if (game->entity.ghost == 1 && game->ghost.appear_counter == 0
		&& game->entity.skely > 0)
		draw_to_map(game, &game->ghost.anim, game->ghost.loc);
	if (game->ghost.activate == 1)
		draw_to_map(game, &game->ghost.effect, game->ghost.loc);
}
