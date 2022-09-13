/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:53:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 17:14:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Place sprite onto the window
**/
static void	place_sprite(t_game *game, char *sprite, int x, int y)
{
	t_image		img;
	t_vector	loc;

	image_init(&img);
	init_vector(&loc);
	loc.x = y * 64;
	loc.y = x * 64;
	img.ref = mlx_xpm_file_to_image(game->ref, sprite,
			&img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ref, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	mlx_put_image_to_window(game->ref, game->window.ref, img.ref, loc.x, loc.y);
	mlx_destroy_image(game->ref, img.ref);
}

/**
 * Get the sprite of the entity
**/
static char	*get_entity_sprite(t_game *game, int x, int y)
{
	char		**map;
	char		enty;
	t_vector	size;

	map = game->map_data.map;
	enty = map[x][y];
	size.x = game->map_data.size.x;
	size.y = game->map_data.size.y;
	if (x == 0 || y == 0 || x == size.y - 1 || y == size.x - 1)
		return (NULL);
	if (enty == 'P')
		return (P);
	if (enty == 'M')
		return (M);
	if (enty == 'G')
		return (G);
	if (enty == '0')
		return (F);
	if (enty == 'C')
		return (C);
	if (enty == '1')
		return (B);
	if (enty == 'E')
		return (EC);
	return (NULL);
}

/**
 * Place entity sprite onto window
**/
void	place_entity_sprite(t_game *game, int x, int y)
{
	char	*enty;

	enty = get_entity_sprite(game, x, y);
	if (enty == NULL)
		return ;
	place_sprite(game, enty, x, y);
}

/**
 * Get the wall sprite
 * 
 * Since the map already been checked to be a valid map. I don't have to
 * check if the wall is consists of only '1'. What I have to know is what's
 * the location (x, y) and place the wall image based on that.
 * 
 * So, this function is to return the respective wall sprite based on the
 * index. If the index does not match any of the condition here, return
 * NULL. This means before pass the wall sprite to mlx function, need
 * to check whether it's NULL or not.
 * TODO: Refactor this shit!
**/
static char	*get_wall_sprite(t_game *game, int x, int y)
{
	int	width;
	int	height;

	width = game->map_data.size.x;
	height = game->map_data.size.y;
	if (x == 0 && y == 0)
		return (WUL);
	else if (x == 0 && y == width - 1)
		return (WUR);
	else if (x == height - 1 && y == 0)
		return (WDL);
	else if (x == height - 1 && y == width - 1)
		return (WDR);
	else if (x == 0 && (y > 0 && y < width - 1))
		return (WU);
	else if (x == height - 1 && (y > 0 && y < width - 1))
		return (WD);
	else if (y == 0 && (x > 0 && x < height - 1))
		return (WL);
	else if (y == width - 1 && (x > 0 && x < height - 1))
		return (WR);
	else if (x == 1 && (y > 0 && y < width - 1))
		return (WV);
	else
		return (NULL);
}

/**
 * Place up down left right wall & vertical wall
 * 
 * If wall is NULL, return.
 * If wall is valid, place sprite onto the window.
**/
void	place_wall_sprite(t_game *game, int x, int y)
{
	char	*wall;

	wall = get_wall_sprite(game, x, y);
	if (wall == NULL)
		return ;
	place_sprite(game, wall, x, y);
}
