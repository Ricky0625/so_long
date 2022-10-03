/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:29:49 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/03 15:23:51 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	draw_vertical_wall(t_game *game, void *content)
{
	t_vwall	*vwall;
	t_image	*map_img;
	t_image	**frames;
	int		*current_frame;

	vwall = content;
	map_img = game->map_img;
	frames = vwall->idle.frames;
	current_frame = &vwall->idle.current_frame;
	if (frames[*current_frame] == 0)
		*current_frame = 0;
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
	frames = skeleton->idle.frames;
	current_frame = &skeleton->idle.current_frame;
	if (frames[*current_frame] == 0)
		*current_frame = 0;
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
	frames = coll->idle.frames;
	current_frame = &coll->idle.current_frame;
	if (frames[*current_frame] == 0)
		*current_frame = 0;
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
	frames = player->idle.frames;
	current_frame = &player->idle.current_frame;
	if (frames[*current_frame] == 0)
		*current_frame = 0;
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
	frames = ghost->idle.frames;
	current_frame = &ghost->idle.current_frame;
	if (frames[*current_frame] == 0)
		*current_frame = 0;
	copy_image(frames[*current_frame], map_img,
		ghost->loc.y * SPT_SIZE, ghost->loc.x * SPT_SIZE);
}
