/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:28:25 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/07 14:40:00 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Check if there is extra newline after the map
 * OR
 * If the map only consists of newline
 * 
 * Before calling this function, we already have the size of the map.
 * And we also have our map in a 2D array format. Since the map is
 * processed using ft_split, meaning the last item of our 2D array
 * must be a NULL. Btw, it's splited using '\n'. If there is 
 * more than 1 '\n' at the end, the array will also ends with NULL
 * 
 * How to check?
 * Iterate through the 2D array. If the current array is NULL AND
 * it's not the end of the map (i < height). Meaning there is
 * extra newline at the end. If that's the case, exit.
**/
void	check_extra_newline(t_game *game, char **map)
{
	int	i;
	int	height;

	i = 0;
	height = game->map_data.size.y;
	while (i < height)
	{
		if (map[i] == NULL && i < height)
		{
			ft_putstr_fd(RED"[ERROR]: Invalid map!\n"DEF, 2);
			free_game(game);
			exit(2);
		}
		i++;
	}
}

/**
 * Check if the wall is valid
 * 
 * 1. Check if the wall is rectangular
 * 2. Check if the wall only constructed using '1'
**/
void	check_wall(t_game *game, char **map)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = game->map_data.size.x;
	height = game->map_data.size.y;
	is_rectangular(game);
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
		{
			if (x == 0 || y == 0 || x == height - 1 || y == width - 1)
			{
				if (map[x][y] != '1')
				{
					ft_putstr_fd(RED"[ERROR]: Invalid wall format!\n"DEF, 2);
					free_game(game);
					exit(2);
				}
			}
		}
	}
}

void	check_essential(t_game *game, char **map)
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
	if (game->enty.coll == 0 || game->enty.exit == 0 || game->enty.plyr == 0
		|| game->enty.exit > 1 || game->enty.plyr > 1)
	{
		ft_putstr_fd(RED"[ERROR]: Invalid map format!\n"DEF, 2);
		ft_putstr_fd(YL"Require 1 (P)layer, 1 (E)xit, 1 (C)ollectible\n"DEF, 2);
		free_game(game);
		exit(2);
	}
}

/**
 * Check valid path
 * 
 * 1. Find where is the starting point (x, y)
 * 2. Create a copy of the map
 * 3. Fill map
 * 4. Check if there is a collectible or exit still exists
 *    in the map
**/
void	check_valid_path(t_game *game, char **map)
{
	t_vector	plyr;
	char		*line;
	char		**fill;
	char		**temp;

	find_entity(&plyr, map, 'P');
	fill = copy_map(game, map);
	fill_map(&plyr, fill);
	temp = fill;
	while (*fill != NULL)
	{
		line = *(fill++);
		while (*line != '\0')
		{
			if (*line == 'C' || *line == 'E')
			{
				ft_putstr_fd(RED"[Error]: Map not playable!\n"DEF, 2);
				free_game(game);
				free(temp);
				exit(2);
			}
			line++;
		}
	}
	free(temp);
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
