/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:56:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/07 14:38:40 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	is_rectangular(t_game *game)
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
		{
			ft_putstr_fd(RED"[ERROR]: Map not rectangular!\n"DEF, 2);
			free_game(game);
			exit(2);
		}
	}
}

void	get_entity(t_game *game, char ch)
{
	if (ch == 'E')
		game->enty.exit += 1;
	else if (ch == 'C')
		game->enty.coll += 1;
	else if (ch == 'P')
		game->enty.plyr += 1;
	else if (ch == 'M')
		game->enty.enem += 1;
	else if (ch == '0' || ch == '1')
		return ;
	else
	{
		ft_putstr_fd(RED"[ERROR]: Invalid character found!\n"DEF, 2);
		free_game(game);
		exit(2);
	}
}

void	find_entity(t_vector *loc, char **map, char enty)
{
	int		x;
	int		y;
	char	*line;

	x = 0;
	y = 0;
	while (*(map + x) != NULL)
	{
		line = *(map + x);
		y = 0;
		while (*(line + y) != '\0')
		{
			if (*(line + y) == enty)
			{
				loc->x = x;
				loc->y = y;
			}
			y++;
		}
		x++;
	}
}

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
