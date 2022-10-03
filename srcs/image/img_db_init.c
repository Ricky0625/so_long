/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_db_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:39:23 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/03 14:18:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void img_db_init(t_game *game)
{
	t_img_db *img_db;

	img_db = &game->img_db;
	img_db->player_idle = ft_calloc(3, sizeof(t_image *));
	img_db->ghost_idle = ft_calloc(3, sizeof(t_image *));
	// img_db->ghost_appear = ft_calloc(3, sizeof(t_image *));
	// img_db->ghost_cutscene = ft_calloc(3, sizeof(t_image *));
	img_db->key_idle = ft_calloc(3, sizeof(t_image *));
	// img_db->key_effect = ft_calloc(3, sizeof(t_image *));
	img_db->skeleton_idle = ft_calloc(3, sizeof(t_image *));
	// img_db->skeleton_killed = ft_calloc(3, sizeof(t_image *));
	// img_db->exit_open = ft_calloc(3, sizeof(t_image *));
	img_db->vwall_idle = ft_calloc(4, sizeof(t_image *));
	img_db->corner_wall = ft_calloc(5, sizeof(t_image *));
	img_db->side_wall = ft_calloc(5, sizeof(t_image *));
}

static void fetch_wall_imgs(t_game *game, t_img_db *img_db)
{
	img_db->corner_wall[0] = xpm_to_image(game, WALL_UL, 1);
	img_db->corner_wall[1] = xpm_to_image(game, WALL_UR, 1);
	img_db->corner_wall[2] = xpm_to_image(game, WALL_DL, 1);
	img_db->corner_wall[3] = xpm_to_image(game, WALL_DR, 1);
	img_db->side_wall[0] = xpm_to_image(game, WALL_U, 1);
	img_db->side_wall[1] = xpm_to_image(game, WALL_L, 1);
	img_db->side_wall[2] = xpm_to_image(game, WALL_R, 1);
	img_db->side_wall[3] = xpm_to_image(game, WALL_D, 1);
}

static void fetch_entity_imgs(t_game *game, t_img_db *img_db)
{
	img_db->player_idle[0] = xpm_to_image(game, PLAYER1, 1);
	img_db->player_idle[1] = xpm_to_image(game, PLAYER2, 1);
	img_db->ghost_idle[0] = xpm_to_image(game, GHOST1, 1);
	img_db->ghost_idle[1] = xpm_to_image(game, GHOST2, 1);
	// img_db->ghost_appear[0] = 0;
	// img_db->ghost_appear[1] = 0;
	// img_db->ghost_cutscene[0] = 0;
	// img_db->ghost_cutscene[1] = 0;
	img_db->key_idle[0] = xpm_to_image(game, KEY1, 1);
	img_db->key_idle[1] = xpm_to_image(game, KEY2, 1);
	// img_db->key_effect[0] = xpm_to_image(game, KEY1, 1);
	// img_db->key_effect[1] = xpm_to_image(game, KEY2, 1);
	img_db->skeleton_idle[0] = xpm_to_image(game, SKELY1, 1);
	img_db->skeleton_idle[1] = xpm_to_image(game, SKELY2, 1);
	// img_db->skeleton_killed[0] = xpm_to_image(game, SKELY1, 1);
	// img_db->skeleton_killed[1] = xpm_to_image(game, SKELY2, 1);
	// img_db->exit_open[0] = 0;
	// img_db->exit_open[1] = 0;
	img_db->vwall_idle[0] = xpm_to_image(game, VWALL1, 1);
	img_db->vwall_idle[1] = xpm_to_image(game, VWALL2, 1);
	img_db->vwall_idle[2] = xpm_to_image(game, VWALL3, 1);
}

void fetch_all_imgs(t_game *game)
{
	t_img_db *img_db;

	img_db_init(game);
	img_db = &game->img_db;
	fetch_wall_imgs(game, img_db);
	fetch_entity_imgs(game, img_db);
	img_db->floor = xpm_to_image(game, FLOOR, 1);
}
