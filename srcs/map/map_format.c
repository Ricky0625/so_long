/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:28:25 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 22:10:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if the map has extra newline
 *
 * Before calling this function, the size of the map has been calculated.
 * Our map is also in a 2D array format. The map is actually created using
 * ft_split and the delimeter is '\n'. Every '\n' will be used to determine
 * the start and end of a line.
 *
 * To check if there's extra newline, we just need to iterate through the map
 * until we reach the last thing of our 2D array, NULL. If the height is not
 * the same as what has calculated previously, meaning there is newline in
 * the map. So, if that's the case, exit the game.
 */
static void	check_extra_newline(t_game *game, char **map)
{
	int	i;
	int	height;

	i = 0;
	height = game->map_data.size.y;
	while (i < height)
	{
		if (map[i] == NULL && i < height)
			exit_game(game, "Invalid map! Extra newline detected.", FAILURE);
		i++;
	}
}

/**
 * @brief Check if the wall is valid
 *
 * 1. Check if the wall is rectangular
 * 2. Check if the wall only consist of '1'
 **/
static void	check_wall(t_game *game, char **map)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = game->map_data.size.x;
	height = game->map_data.size.y;
	check_if_rectangular(game);
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
		{
			if ((x == 0 || y == 0 || x == height - 1 || y == width - 1)
				&& map[x][y] != '1')
				exit_game(game, "Invalid wall format!", FAILURE);
		}
	}
}

/**
 * @brief Check if the map setup is valid.
 *
 * Mandatory setup:
 * 1. At least one (C)ollectible
 * 2. Only one (P)layer
 * 3. Only one (E)xit
 *
 * Advanced setup:
 * 1. Only one (G)host
 * 2. If there is at least one skeleton (M), there must have one ghost
 **/
static void	check_essential(t_game *game, char **map)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = game->map_data.size.x;
	height = game->map_data.size.y;
	x = 0;
	while (++x < height - 1)
	{
		y = 0;
		while (++y < width - 1)
			get_entity(game, map[x][y]);
	}
	if (game->entity.coll == 0 || game->entity.exit != 1
		|| game->entity.plyr != 1 || game->entity.ghost > 1
		|| (game->entity.ghost == 0 && game->entity.skely > 0))
	{
		ft_printf(YL "Require 1 (P)layer, 1 (E)xit, 1 (C)ollectible.\n" DEF);
		ft_printf(YL "If there's enemy, there must be a ghost.\n" DEF);
		exit_game(game, "Invalid map setup!", FAILURE);
	}
}

/**
 * @brief Check if there's a valid path
 *
 * 1. Find where is the starting point (x, y)
 * 2. Create a copy of the map
 * 3. Fill map
 * 4. Check if there is a collectible or exit still exists
 *    in the map
 **/
static void	check_valid_path(t_game *game, char **map)
{
	t_vector	plyr;
	char		*line;
	char		**fill;
	char		**temp;

	find_entity(&plyr, map, 'P');
	fill = fill_map(game, plyr);
	temp = fill;
	while (*fill != NULL)
	{
		line = *(fill++);
		while (*line != '\0')
		{
			if (*line == 'C' || *line == 'E')
			{
				free_map(temp);
				exit_game(game, "Map not playable!", FAILURE);
			}
			line++;
		}
	}
	free_map(temp);
}

/**
 * Check if the map is valid
 *
 * 1. Check if there is no trailing newline
 * 2. Check if the wall is rectangular and only consists of '1'
 * 3. Check all the essential item is in the map
 * 4. Check if there is a valid path
 * 5. If every test above does not have any error, then map will be
 *    assigned to map_data.map. Which means this is a playable and
 * 	  valid map.
 **/
void	check_map_format(t_game *game)
{
	char	**map;

	map = game->map_data.map;
	check_extra_newline(game, map);
	check_wall(game, map);
	check_essential(game, map);
	check_valid_path(game, map);
}
