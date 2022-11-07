/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:29:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 16:40:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Free map
**/
void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i] != NULL)
		free(map[i]);
	free(map);
}

void	free_map_data(t_game *game)
{
	if (game->map_data.map != NULL)
		free_map(game->map_data.map);
	// if (game->map_data.file != NULL)
	// 	free(game->map_data.file);
	// if (game->map_data.raw != NULL)
	// 	free(game->map_data.raw);
}

void	free_img(t_image *img)
{
	if (img == NULL)
		return ;
	if (img->data != 0)
		free(img->data);
	// free(img->ref);
	free(img);
}

void	free_img_arr(t_image **arr)
{
	t_image	*img;

	while (*arr != NULL)
	{
		img = *arr;
		free_img(img);
		arr++;
	}
	arr = NULL;
}

void	free_img_db(t_game *game)
{
	t_img_db *img_db;

	img_db = &game->img_db;
	free_img(game->img_db.block);
	free_img(game->img_db.floor);
	free_img(game->img_db.corner_down_left);
	free_img(game->img_db.corner_down_right);
	free_img(game->img_db.corner_up_left);
	free_img(game->img_db.corner_up_right);
	free_img(game->img_db.side_up);
	free_img(game->img_db.side_down);
	free_img(game->img_db.side_left);
	free_img(game->img_db.side_right);
	free_img(game->bg.img);
	free_img_arr(img_db->player_idle_l);
	free_img_arr(img_db->player_idle_r);
	free_img_arr(img_db->ghost_idle);
	free_img_arr(img_db->ghost_boo);
	free_img_arr(img_db->key_idle);
	free_img_arr(img_db->skeleton_idle_l);
	free_img_arr(img_db->skeleton_idle_r);
	free_img_arr(img_db->skeleton_scared);
	free_img_arr(img_db->exit);
	free_img_arr(img_db->vwall_idle);
	free_img_arr(img_db->numbers);
}

/**
 * Free the game
 * 
 * 1. Free the raw map
 * 2. Free the map
 * 3. Free game
**/
void	free_game(t_game *game)
{
	free_img_db(game);
	free(game->map_data.raw);
	free_map(game->map_data.map);
	free(game->ref);
	free(game);
}
