/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:29:49 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:39:58 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Draw the image to the map_img
 */
void	draw_to_map(t_image *map_img, t_anim *anim, t_vector loc)
{
	t_image	*frame;
	int		current_frame;

	current_frame = anim->current_frame;
	frame = anim->frames[current_frame];
	copy_image(frame, map_img,
		loc.y * SPT_SIZE, loc.x * SPT_SIZE);
}

/**
 * @brief Draw the image of each node of a linked list to the screen
 */
void	lst_draw_frame(t_image *map_img, t_list *lst, t_enty_type type,
	void (*draw)(t_image *, t_anim *, t_vector loc))
{
	t_skeleton	*skely;
	t_coll		*coll;
	t_vwall		*vwall;

	while (lst != NULL)
	{
		if (type == SKELETON)
		{
			skely = lst->content;
			draw(map_img, &skely->anim, skely->loc);
		}
		else if (type == COLLECTIBLE)
		{
			coll = lst->content;
			draw(map_img, &coll->anim, coll->loc);
		}
		else if (type == VWALL)
		{
			vwall = lst->content;
			draw(map_img, &vwall->anim, vwall->loc);
		}
		lst = lst->next;
	}
}

/**
 * @brief Draw scared skeletons, will be run after the ghost
 *        is activated
 */
void	draw_scared_skeletons(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	if (game->skeletons == NULL)
		return ;
	skeletons = game->skeletons;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		if (skely->anim.current_frame < 6)
			update_frame(&skely->anim);
		skeletons = skeletons->next;
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
	t_image	*map_img;

	map_img = game->map_img;
	lst_draw_frame(map_img, game->skeletons, SKELETON, draw_to_map);
	lst_draw_frame(map_img, game->collectibles, COLLECTIBLE, draw_to_map);
	lst_draw_frame(map_img, game->vwalls, VWALL, draw_to_map);
	draw_to_map(map_img, &game->exit.anim, game->exit.loc);
	draw_to_map(map_img, &game->player.anim, game->player.loc);
	if (game->entity.ghost == 1 && game->ghost.appear_counter == 0
		&& game->entity.skely > 0)
		draw_to_map(map_img, &game->ghost.anim, game->ghost.loc);
	if (game->ghost.activate == 1)
		draw_to_map(map_img, &game->ghost.effect, game->ghost.loc);
}
