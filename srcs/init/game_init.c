/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:57:44 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 17:41:48 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

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
static void	metatdata_init(t_game *game)
{
	game->map_data.map = NULL;
	vector_init(&game->map_data.size);
	game->enty.coll = 0;
	game->enty.enem = 0;
	game->enty.exit = 0;
	game->enty.plyr = 0;
	game->enty.ghost = 0;
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
	metatdata_init(game);
	file = av[ac - 1];
	map_validator(game, file);
	return (game);
}
