/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:29:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/07 14:20:41 by wricky-t         ###   ########.fr       */
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

/**
 * Free the game
 * 
 * 1. Free the raw map
 * 2. Free the map
 * 3. Free game
**/
void	free_game(t_game *game)
{
	free(game->map_data.raw);
	free_map(game->map_data.map);
	free(game);
}
