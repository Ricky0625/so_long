/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:07:36 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 17:31:47 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Place sprite onto the window
**/
void	place_sprite(t_game *game, char *sprite, int x, int y)
{
	t_image		img;
	t_vector	loc;

	image_init(&img);
	vector_init(&loc);
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
 * Iterate through the map, run (*f) on each of the character.
 * 
 * Takes in two argument, game & a function pointer.
 * The function pointer needs to be the function that is responsible
 * to place image.
 * 
 * line : the line of the map
 * map  : the map
 * index: index vector
**/
void	mapiteri(t_game *game, void (*f)(t_game *, int, int))
{
	char		*line;
	char		**map;
	t_vector	index;

	map = game->map_data.map;
	vector_init(&index);
	while (*map != NULL)
	{
		line = *map;
		index.y = 0;
		while (*line != '\0')
		{
			f(game, index.x, index.y);
			index.y += 1;
			line++;
		}
		index.x += 1;
		map++;
	}
}

/**
 * Place the map
 * 1. Place wall sprite
 * 2. Place the remaining sprite besides wall
**/
void	place_map(t_game *game)
{
	mapiteri(game, place_wall_sprite);
	mapiteri(game, place_entity_sprite);
	place_sprite(game, P,
		game->player.player.loc.x, game->player.player.loc.y);
}
