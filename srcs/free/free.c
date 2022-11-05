/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:29:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 22:26:23 by wricky-t         ###   ########.fr       */
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

void	free_img_db(t_game *game)
{
	t_img_db *img_db;

	img_db = &game->img_db;
	if (img_db == NULL)
		return ;
	free(img_db->player_idle_l);
	free(img_db->player_idle_r);
	free(img_db->ghost_idle);
	free(img_db->ghost_boo);
	free(img_db->key_idle);
	free(img_db->skeleton_idle_l);
	free(img_db->skeleton_idle_r);
	free(img_db->skeleton_scared);
	free(img_db->exit);
	free(img_db->vwall_idle);
	free(img_db->numbers);
	img_db->block = NULL;
	img_db->floor = NULL;
	img_db->side_down = NULL;
	img_db->side_up = NULL;
	img_db->side_left = NULL;
	img_db->side_right = NULL;
	img_db->corner_down_left = NULL;
	img_db->corner_down_right = NULL;
	img_db->corner_up_left = NULL;
	img_db->corner_up_right = NULL;
	img_db = NULL;
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
	free(game);
}
