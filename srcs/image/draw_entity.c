/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:29:49 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 16:22:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
/**
 * @brief 
 * 
 * @param game 
 * @param content 
 */
void	draw_vertical_wall(t_game *game, void *content)
{
	t_vwall	*vwall;
	t_image	*map_img;
	t_image	**frames;
	int		*current_frame;

	vwall = content;
	map_img = game->map_img;
	frames = vwall->anim.frames;
	current_frame = &vwall->anim.current_frame;
	copy_image(frames[*current_frame], map_img,
		vwall->loc.y * SPT_SIZE, vwall->loc.x * SPT_SIZE);
}

void	draw_skeletons(t_game *game, void *content)
{
	t_skeleton	*skeleton;
	t_image		*map_img;
	t_image		**frames;
	int			*current_frame;

	skeleton = content;
	map_img = game->map_img;
	frames = skeleton->anim.frames;
	current_frame = &skeleton->anim.current_frame;
	copy_image(frames[*current_frame], map_img,
		skeleton->loc.y * SPT_SIZE, skeleton->loc.x * SPT_SIZE);
}

void	draw_colls(t_game *game, void *content)
{
	t_coll	*coll;
	t_image	*map_img;
	t_image	**frames;
	int		*current_frame;

	coll = content;
	map_img = game->map_img;
	frames = coll->anim.frames;
	current_frame = &coll->anim.current_frame;
	copy_image(frames[*current_frame], map_img,
		coll->loc.y * SPT_SIZE, coll->loc.x * SPT_SIZE);
}

void	draw_player(t_game *game)
{
	t_player	*player;
	t_image		*map_img;
	t_image		**frames;
	int			*current_frame;

	player = &game->player;
	map_img = game->map_img;
	frames = player->anim.frames;
	current_frame = &player->anim.current_frame;
	copy_image(frames[*current_frame], map_img,
		player->loc.y * SPT_SIZE, player->loc.x * SPT_SIZE);
}

void	draw_ghost(t_game *game)
{
	t_ghost	*ghost;
	t_image	*map_img;
	t_image	**frames;
	int		*current_frame;

	ghost = &game->ghost;
	map_img = game->map_img;
	frames = ghost->anim.frames;
	current_frame = &ghost->anim.current_frame;
	copy_image(frames[*current_frame], map_img,
		ghost->loc.y * SPT_SIZE, ghost->loc.x * SPT_SIZE);
}
