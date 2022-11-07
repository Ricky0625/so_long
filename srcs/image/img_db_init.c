/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_db_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:39:23 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 17:46:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initialize image database
 * 
 * TODO: free all these shit before exit
 */
static void	img_db_init(t_game *game)
{
	t_img_db	*img_db;

	img_db = &game->img_db;
	img_db->player_idle_l = ft_calloc(5, sizeof(t_image *));
	img_db->player_idle_r = ft_calloc(5, sizeof(t_image *));
	img_db->ghost_idle = ft_calloc(5, sizeof(t_image *));
	img_db->ghost_boo = ft_calloc(6, sizeof(t_image *));
	img_db->key_idle = ft_calloc(5, sizeof(t_image *));
	img_db->skeleton_idle_l = ft_calloc(4, sizeof(t_image *));
	img_db->skeleton_idle_r = ft_calloc(4, sizeof(t_image *));
	img_db->skeleton_scared = ft_calloc(8, sizeof(t_image *));
	img_db->exit = ft_calloc(7, sizeof(t_image *));
	img_db->vwall_idle = ft_calloc(5, sizeof(t_image *));
	img_db->numbers = ft_calloc(11, sizeof(t_image *));
}

static void	fetch_other_imgs(t_game *game, t_img_db *img_db)
{
	img_db->exit[0] = xpm_to_image(game, EXIT1, 1);
	img_db->exit[1] = xpm_to_image(game, EXIT2, 1);
	img_db->exit[2] = xpm_to_image(game, EXIT3, 1);
	img_db->exit[3] = xpm_to_image(game, EXIT4, 1);
	img_db->exit[4] = xpm_to_image(game, EXIT5, 1);
	img_db->exit[5] = xpm_to_image(game, EXIT6, 1);
	img_db->side_up = xpm_to_image(game, WALL_U, 1);
	img_db->side_down = xpm_to_image(game, WALL_D, 1);
	img_db->side_left = xpm_to_image(game, WALL_L, 1);
	img_db->side_right = xpm_to_image(game, WALL_R, 1);
	img_db->corner_up_left = xpm_to_image(game, WALL_UL, 1);
	img_db->corner_up_right = xpm_to_image(game, WALL_UR, 1);
	img_db->corner_down_left = xpm_to_image(game, WALL_DL, 1);
	img_db->corner_down_right = xpm_to_image(game, WALL_DR, 1);
	img_db->vwall_idle[0] = xpm_to_image(game, VWALL1, 1);
	img_db->vwall_idle[1] = xpm_to_image(game, VWALL2, 1);
	img_db->vwall_idle[2] = xpm_to_image(game, VWALL3, 1);
	img_db->vwall_idle[3] = xpm_to_image(game, VWALL4, 1);
	img_db->key_idle[0] = xpm_to_image(game, KEY1, 1);
	img_db->key_idle[1] = xpm_to_image(game, KEY2, 1);
	img_db->key_idle[2] = xpm_to_image(game, KEY3, 1);
	img_db->key_idle[3] = xpm_to_image(game, KEY4, 1);
}

void	fetch_entity_imgs(t_game *game, t_img_db *img_db)
{
	img_db->player_idle_l[0] = xpm_to_image(game, PLAYERL1, 1);
	img_db->player_idle_l[1] = xpm_to_image(game, PLAYERL2, 1);
	img_db->player_idle_l[2] = xpm_to_image(game, PLAYERL3, 1);
	img_db->player_idle_l[3] = xpm_to_image(game, PLAYERL4, 1);
	img_db->player_idle_r[0] = xpm_to_image(game, PLAYERR1, 1);
	img_db->player_idle_r[1] = xpm_to_image(game, PLAYERR2, 1);
	img_db->player_idle_r[2] = xpm_to_image(game, PLAYERR3, 1);
	img_db->player_idle_r[3] = xpm_to_image(game, PLAYERR4, 1);
	img_db->skeleton_idle_l[0] = xpm_to_image(game, SKELYL1, 1);
	img_db->skeleton_idle_l[1] = xpm_to_image(game, SKELYL2, 1);
	img_db->skeleton_idle_l[2] = xpm_to_image(game, SKELYL3, 1);
	img_db->skeleton_idle_r[0] = xpm_to_image(game, SKELYR1, 1);
	img_db->skeleton_idle_r[1] = xpm_to_image(game, SKELYR2, 1);
	img_db->skeleton_idle_r[2] = xpm_to_image(game, SKELYR3, 1);
	img_db->ghost_idle[0] = xpm_to_image(game, GHOST1, 1);
	img_db->ghost_idle[1] = xpm_to_image(game, GHOST2, 1);
	img_db->ghost_idle[2] = xpm_to_image(game, GHOST3, 1);
	img_db->ghost_idle[3] = xpm_to_image(game, GHOST4, 1);
}

static void	fetch_effect_imgs(t_game *game, t_img_db *img_db)
{
	img_db->ghost_boo[0] = xpm_to_image(game, BOO1, 1);
	img_db->ghost_boo[1] = xpm_to_image(game, BOO2, 1);
	img_db->ghost_boo[2] = xpm_to_image(game, BOO3, 1);
	img_db->ghost_boo[3] = xpm_to_image(game, BOO4, 1);
	img_db->ghost_boo[4] = xpm_to_image(game, BOO5, 1);
	img_db->skeleton_scared[0] = xpm_to_image(game, SCARED1, 1);
	img_db->skeleton_scared[1] = xpm_to_image(game, SCARED2, 1);
	img_db->skeleton_scared[2] = xpm_to_image(game, SCARED3, 1);
	img_db->skeleton_scared[3] = xpm_to_image(game, SCARED4, 1);
	img_db->skeleton_scared[4] = xpm_to_image(game, SCARED5, 1);
	img_db->skeleton_scared[5] = xpm_to_image(game, SCARED6, 1);
	img_db->skeleton_scared[6] = xpm_to_image(game, SCARED7, 1);
	img_db->numbers[0] = xpm_to_image(game, ZERO, 1);
	img_db->numbers[1] = xpm_to_image(game, ONE, 1);
	img_db->numbers[2] = xpm_to_image(game, TWO, 1);
	img_db->numbers[3] = xpm_to_image(game, THREE, 1);
	img_db->numbers[4] = xpm_to_image(game, FOUR, 1);
	img_db->numbers[5] = xpm_to_image(game, FIVE, 1);
	img_db->numbers[6] = xpm_to_image(game, SIX, 1);
	img_db->numbers[7] = xpm_to_image(game, SEVEN, 1);
	img_db->numbers[8] = xpm_to_image(game, EIGHT, 1);
	img_db->numbers[9] = xpm_to_image(game, NINE, 1);
}

/**
 * @brief Fetch all the images to get the image database ready
 */
void	fetch_all_imgs(t_game *game)
{
	t_img_db	*img_db;

	img_db_init(game);
	img_db = &game->img_db;
	game->bg.img = xpm_to_image(game, BG, 0);
	vector_init(&game->bg.position);
	img_db->floor = xpm_to_image(game, FLOOR, 1);
	img_db->block = xpm_to_image(game, BLOCK, 1);
	fetch_other_imgs(game, img_db);
	fetch_entity_imgs(game, img_db);
	fetch_effect_imgs(game, img_db);
}
