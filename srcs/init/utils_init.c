/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:28:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/16 12:15:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize map struct
**/
void	map_init(t_map *map_data)
{
	map_data->raw = 0;
	map_data->map = 0;
	map_data->file = 0;
	vector_init(&map_data->size);
}

/**
 * Initialize tile struct
**/
void	tile_init(t_tile *tile)
{
	tile->type = 0;
	tile->prev = 0;
	vector_init(&tile->loc);
	tile->up = 0;
	tile->down = 0;
	tile->left = 0;
	tile->right = 0;
}

/**
 * Initialize image
 * REMIND: Maybe no use
**/
void	image_init(t_image *img)
{
	img->ref = 0;
	vector_init(&img->size);
	img->pixels = 0;
	img->bits_per_pixel = 0;
	img->line_size = 0;
	img->endian = 0;
}

/**
 * Initialize vector
**/
void	vector_init(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

/**
 * Set vector with given parameter
**/
void	set_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}
