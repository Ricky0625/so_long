/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/08 14:59:23 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Pathfinder visualizer
**/
void	show_path(char **map)
{
	char	*line;

	while (*map != NULL)
	{
		line = *map;
		while (*line != '\0')
		{
			if (*line != '0' && *line != 'F' && *line != 'C' && *line != 'E')
				ft_putchar_fd(*line, 1);
			else if (*line == 'C')
				ft_putstr_fd(YL"C"DEF, 1);
			else if (*line == 'E')
				ft_putstr_fd(RED"E"DEF, 1);
			else if (*line == 'F')
				ft_putstr_fd(GN"▉"DEF, 1);
			else
				ft_putchar_fd(' ', 1);
			line++;
		}
		ft_putchar_fd('\n', 1);
		map++;
	}
}

/**
 * A recursive function to replace '0', 'C' 'E' & 'P' to 'F'.
 * When a character is replaced to 'F' meaning the player can
 * go to that space without blocked.
 * 
 * The base case is met if it encounters a wall or a filled space.
**/
static void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'F')
		return ;
	map[x][y] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

/**
 * Check if the surrounding is not '1' && 'P'
**/
void	fill_map(t_vector *start, char **fill)
{
	int	x;
	int	y;

	x = start->x;
	y = start->y;
	flood_fill(fill, x, y);
}
