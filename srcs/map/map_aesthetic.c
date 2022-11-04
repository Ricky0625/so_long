/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aesthetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:44:03 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:33:59 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Create a horizontal wall for aesthetic purpose
 * 
 * Horizontal wall format: "1VVVVVVVVVV1"
 * Start & ends with '1', the rest will be 'V'
**/
static char	*add_horizontal_wall(t_game *game)
{
	int		i;
	int		width;
	char	*v_wall;

	i = 0;
	width = game->map_data.size.x;
	v_wall = malloc(sizeof(char) * (width + 1));
	if (v_wall == NULL)
		return (NULL);
	while (i < width)
	{
		if (i == 0 || i == width - 1)
			v_wall[i] = '1';
		else
			v_wall[i] = 'V';
		i++;
	}
	v_wall[i] = '\0';
	return (v_wall);
}

/**
 * @brief Add one more line for horizontal wall to add some aesthetic look
 *        for the game.
 * 
 * Update the map to add a horizontal wall after the wall.
**/
char	**add_aesthetic(t_game *game)
{
	char	**map;
	char	**new;
	int		height;
	int		i;

	map = game->map_data.map;
	height = game->map_data.size.y + 1;
	new = malloc(sizeof(char *) * (height + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (*map != NULL)
	{
		if (i == 1)
			new[i++] = add_horizontal_wall(game);
		else
			new[i++] = *(map++);
	}
	new[i] = NULL;
	game->map_data.map = new;
	game->map_data.size.y += 1;
	return (new);
}
