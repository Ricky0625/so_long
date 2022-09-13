/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:57:44 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 17:25:24 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize vector
**/
void	init_vector(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

/**
 * Initialize the metadata of image
**/
void	image_init(t_image *image)
{
	image->bits_per_pixel = 0;
	image->endian = 0;
	image->line_size = 0;
	image->pixels = 0;
	image->size.x = 0;
	image->size.y = 0;
}

/**
 * Initialize all the metadata
**/
static void	init_metadata(t_game *game)
{
	game->map_data.map = NULL;
	init_vector(&game->map_data.size);
	game->enty.coll = 0;
	game->enty.enem = 0;
	game->enty.exit = 0;
	game->enty.plyr = 0;
}

/**
 * Initialize the game
**/
t_game	*game_init(int ac, char **av)
{
	t_game	*game;
	char	*file;

	if (ac != 2)
	{
		ft_putstr_fd(RED"[ERROR]: Invalid Usage!\n"DEF, 2);
		exit(EXIT_FAILURE);
	}
	game = malloc(sizeof(t_game));
	game->ref = mlx_init();
	init_metadata(game);
	file = av[ac - 1];
	map_validator(game, file);
	return (game);
}
