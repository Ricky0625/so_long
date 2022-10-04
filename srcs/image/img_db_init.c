/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_db_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:39:23 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 15:47:00 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	img_db_init(t_game *game)
{
	t_img_db	*img_db;

	img_db = &game->img_db;
	img_db->player_idle = ft_calloc(7, sizeof(t_image *));
	img_db->ghost_idle = ft_calloc(7, sizeof(t_image *));
	// img_db->ghost_appear = ft_calloc(3, sizeof(t_image *));
	// img_db->ghost_cutscene = ft_calloc(3, sizeof(t_image *));
	img_db->key_idle = ft_calloc(7, sizeof(t_image *));
	// img_db->key_effect = ft_calloc(3, sizeof(t_image *));
	img_db->skeleton_idle = ft_calloc(5, sizeof(t_image *));
	// img_db->skeleton_killed = ft_calloc(3, sizeof(t_image *));
	img_db->exit = ft_calloc(7, sizeof(t_image *));
	img_db->vwall_idle = ft_calloc(7, sizeof(t_image *));
	img_db->corner_wall = ft_calloc(5, sizeof(t_image *));
	img_db->side_wall = ft_calloc(5, sizeof(t_image *));
}

static void	fetch_wall_imgs(t_game *game, t_img_db *img_db)
{
	img_db->corner_wall[0] = xpm_to_image(game, WALL_UL, 1);
	img_db->corner_wall[1] = xpm_to_image(game, WALL_UR, 1);
	img_db->corner_wall[2] = xpm_to_image(game, WALL_DL, 1);
	img_db->corner_wall[3] = xpm_to_image(game, WALL_DR, 1);
	img_db->side_wall[0] = xpm_to_image(game, WALL_U, 1);
	img_db->side_wall[1] = xpm_to_image(game, WALL_L, 1);
	img_db->side_wall[2] = xpm_to_image(game, WALL_R, 1);
	img_db->side_wall[3] = xpm_to_image(game, WALL_D, 1);
	img_db->vwall_idle[0] = xpm_to_image(game, VWALL1, 1);
	img_db->vwall_idle[1] = xpm_to_image(game, VWALL2, 1);
	img_db->vwall_idle[2] = xpm_to_image(game, VWALL3, 1);
	img_db->vwall_idle[3] = xpm_to_image(game, VWALL4, 1);
	img_db->vwall_idle[4] = xpm_to_image(game, VWALL3, 1);
	img_db->vwall_idle[5] = xpm_to_image(game, VWALL2, 1);
}

static void	fetch_entity_imgs(t_game *game, t_img_db *img_db)
{
	img_db->player_idle[0] = xpm_to_image(game, PLAYER1, 1);
	img_db->player_idle[1] = xpm_to_image(game, PLAYER2, 1);
	img_db->player_idle[2] = xpm_to_image(game, PLAYER3, 1);
	img_db->player_idle[3] = xpm_to_image(game, PLAYER4, 1);
	img_db->player_idle[4] = xpm_to_image(game, PLAYER3, 1);
	img_db->player_idle[5] = xpm_to_image(game, PLAYER2, 1);
	img_db->ghost_idle[0] = xpm_to_image(game, GHOST1, 1);
	img_db->ghost_idle[1] = xpm_to_image(game, GHOST2, 1);
	img_db->ghost_idle[2] = xpm_to_image(game, GHOST3, 1);
	img_db->ghost_idle[3] = xpm_to_image(game, GHOST4, 1);
	img_db->ghost_idle[4] = xpm_to_image(game, GHOST3, 1);
	img_db->ghost_idle[5] = xpm_to_image(game, GHOST2, 1);
	img_db->key_idle[0] = xpm_to_image(game, KEY1, 1);
	img_db->key_idle[1] = xpm_to_image(game, KEY2, 1);
	img_db->key_idle[2] = xpm_to_image(game, KEY3, 1);
	img_db->key_idle[3] = xpm_to_image(game, KEY4, 1);
	img_db->key_idle[4] = xpm_to_image(game, KEY3, 1);
	img_db->key_idle[5] = xpm_to_image(game, KEY2, 1);
	img_db->skeleton_idle[0] = xpm_to_image(game, SKELY1, 1);
	img_db->skeleton_idle[1] = xpm_to_image(game, SKELY2, 1);
	img_db->skeleton_idle[2] = xpm_to_image(game, SKELY3, 1);
	img_db->skeleton_idle[3] = xpm_to_image(game, SKELY2, 1);
	img_db->exit[0] = xpm_to_image(game, EXIT1, 1);
	img_db->exit[1] = xpm_to_image(game, EXIT2, 1);
	img_db->exit[2] = xpm_to_image(game, EXIT3, 1);
	img_db->exit[3] = xpm_to_image(game, EXIT4, 1);
	img_db->exit[4] = xpm_to_image(game, EXIT5, 1);
	img_db->exit[5] = xpm_to_image(game, EXIT6, 1);
}

void	fetch_all_imgs(t_game *game)
{
	t_img_db	*img_db;

	img_db_init(game);
	img_db = &game->img_db;
	fetch_wall_imgs(game, img_db);
	fetch_entity_imgs(game, img_db);
	img_db->floor = xpm_to_image(game, FLOOR, 1);
}
