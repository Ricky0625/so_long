/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:56:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:11:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if the map is rectangular or not. If it's not exit game.
 *
 * len	: the length of the line that being inspected right now
 * width: width of the map
 * map	: the map
 *
 * Iterate through the map, line by line. While iterating, get the length
 * of that line. Check if the length is equal to the expected width. If
 * not exit program.
 **/
void	check_if_rectangular(t_game *game)
{
	int		len;
	int		width;
	char	**map;

	width = game->map_data.size.x;
	map = game->map_data.map;
	while (*map != NULL)
	{
		len = ft_strlen(*(map++));
		if (len != width)
			exit_game(game, "Map not rectangular!", FAILURE);
	}
}

/**
 * @brief Count how many entity are there in the map and update the entity
 * 		  stats struct
 *
 * E : Exit
 * C : Collectibles
 * P : Player
 * M : Monster
 * 0 : Empty space
 * 1 : Block
 *
 * If detected any unrecognized character, exit program.
 */
void	get_entity(t_game *game, char ch)
{
	if (ch == 'E')
		game->entity.exit++;
	else if (ch == 'C')
		game->entity.coll++;
	else if (ch == 'P')
		game->entity.plyr++;
	else if (ch == 'M')
		game->entity.skely++;
	else if (ch == 'G')
		game->entity.ghost++;
	else if (ch == '0' || ch == '1')
		return ;
	else
		exit_game(game, "Invalid character found!", FAILURE);
}

/**
 * @brief Locate where is the entity.
 *
 * Iterate through the map, if the current character is the entity we are
 * searching for, set location (x & y).
 */
int	find_entity(t_vector *loc, char **map, char entity)
{
	int		x;
	int		y;
	int		found;
	char	*line;

	x = 0;
	y = 0;
	found = 0;
	while (*(map + x) != NULL)
	{
		line = *(map + x);
		y = 0;
		while (*(line + y) != '\0')
		{
			if (*(line + y) == entity)
			{
				set_vector(loc, x, y);
				found = 1;
			}
			y++;
		}
		x++;
	}
	return (found);
}

/**
 * @brief Copy map. Duh.
 **/
char	**copy_map(t_game *game, char **map)
{
	int		i;
	int		height;
	char	**copy;

	i = 0;
	height = game->map_data.size.y;
	copy = malloc(sizeof(char *) * (height + 1));
	if (copy == NULL)
		return (NULL);
	while (*map != NULL)
	{
		copy[i] = ft_strdup(*map);
		map++;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
