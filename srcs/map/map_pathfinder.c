/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:05:57 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Pathfinder visualizer
 */
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
			else if (*line == 'O')
				ft_putstr_fd(YL"▉"DEF, 1);
			else
				ft_putchar_fd(' ', 1);
			line++;
		}
		ft_putchar_fd('\n', 1);
		map++;
	}
}

/**
 * @brief Floodfill algorithm to fill all passable path as another character
 * 
 * Since the game has an advanced setup: Ghost & Skeleton
 * Ghost: Can help kill the skeletons
 * Skeleton: Enemy
 * 
 * If the game is in advanced setup, we need to first check if the player
 * can reach the ghost without any obstacles that will block them. To do
 * so, I replaced the character to 'O' first. If can reach ghost, meaning
 * we can basically ignore all the skeletons. So this function will replace
 * 'M' to the filled character, which is 'F'.
 * 
 * A recursive function to replace '0', 'C' 'E' & 'P' to 'F'.
 * When a character is replaced to 'F' meaning the player can
 * go to that space without blocked.
 * 
 * Basic setup
 * The base case is met if it encounters a wall or a filled space.
 * 
 * Advanced setup
 * The base case will be if it encounters a wall, filled space ('O' / 'F'),
 * 'M' if cannot reach ghost.
 */
static void	flood_fill(char **map, int x, int y, int can_reach_ghost)
{
	if (map[x][y] == 'G')
		can_reach_ghost = 1;
	if (map[x][y] == '1' || map[x][y] == 'F'
		|| (map[x][y] == 'O' && can_reach_ghost == 0)
		|| (map[x][y] == 'M' && can_reach_ghost == 0))
		return ;
	if (can_reach_ghost == 0)
		map[x][y] = 'O';
	else if (can_reach_ghost == 1)
		map[x][y] = 'F';
	flood_fill(map, x + 1, y, can_reach_ghost);
	flood_fill(map, x - 1, y, can_reach_ghost);
	flood_fill(map, x, y + 1, can_reach_ghost);
	flood_fill(map, x, y - 1, can_reach_ghost);
}

/**
 * @brief The main driver function to floodfill the map
 */
char	**fill_map(t_game *game, t_vector start)
{
	char	**fill;

	fill = copy_map(game, game->map_data.map);
	flood_fill(fill, start.x, start.y, 0);
	return (fill);
}
