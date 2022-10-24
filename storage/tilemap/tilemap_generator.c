/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:19:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/21 17:49:58 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Allocate memory for the tilemap
**/
static t_tile	**alloc_tilemap(t_game *game)
{
	int		i;
	int		width;
	int		height;
	t_tile	**tilemap;

	width = game->map_data.size.x;
	height = game->map_data.size.y;
	tilemap = malloc(sizeof(t_tile *) * (height + 1));
	if (tilemap == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		tilemap[i] = malloc(sizeof(t_tile) * (width + 1));
		if (tilemap[i] == NULL)
			return (NULL);
		i++;
	}
	tilemap[height] = NULL;
	return (tilemap);
}

static t_tiletype	get_tiletype(char ch)
{
	if (ch == 'P')
		return (PLAYER);
	else if (ch == '0')
		return (FLOOR);
	else if (ch == '1')
		return (WALL);
	else if (ch == 'V')
		return (VWALL);
	else if (ch == 'C')
		return (COLLECTIBLE);
	else if (ch == 'M')
		return (SKELETON);
	else if (ch == 'G')
		return (GHOST);
	else if (ch == 'E')
		return (EXIT);
	return (0);
}

/**
 * HEYYO: If something wrong with the image placing, switch x & y here
**/
static void	set_tile(t_tile **tilemap, int x, int y)
{
	tilemap[x][y].prev = tilemap[x][y].type;
	tilemap[x][y].loc.x = x;
	tilemap[x][y].loc.y = y;
	if (x != 0)
		tilemap[x][y].up = &tilemap[x - 1][y];
	if (tilemap[x + 1] != NULL)
		tilemap[x][y].down = &tilemap[x + 1][y];
	if (y != 0)
		tilemap[x][y].left = &tilemap[x][y - 1];
	tilemap[x][y].right = &tilemap[x][y + 1];
}

static void	set_tilemap(char **map, t_tile **tilemap)
{
	int		x;
	int		y;
	char	tile;

	x = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			tile = map[x][y];
			tile_init(&tilemap[x][y]);
			tilemap[x][y].type = get_tiletype(tile);
			set_tile(tilemap, x, y);
			y++;
		}
		tilemap[x][y].type = 0;
		x++;
	}
}

/**
 * Convert 2D array of map into 2D array of tilemap
 * 
 * Tilemap will have more data and will be easier to work on
**/
void	tilemap_generator(t_game *game)
{
	char	**map;
	t_tile	**tilemap;

	map = game->map_data.map;
	tilemap = alloc_tilemap(game);
	if (tilemap == NULL)
	{
		ft_putstr_fd("[ERROR]: Failed to malloc tilemap!\n", 2);
		exit(EXIT_FAILURE);
	}
	set_tilemap(map, tilemap);
	game->tilemap = tilemap;
}
