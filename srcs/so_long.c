/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/25 17:38:33 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initialize the game, basically everything
**/
static void	game_init(t_game *game)
{
	game->ref = mlx_init();
	entity_init(&game->entity);
	game->skeleton = NULL;
	game->collectibles = NULL;
	game->vwall = NULL;
}

/**
 * Start the game
 * 
 * 1. Initialize game
 * 2. Parse map
**/
static t_game	*start_game(int ac, char **av)
{
	t_game	*game;
	char	*file;

	if (ac != 2)
	{
		ft_putstr_fd(RED"[ERROR]: Invalid Usage!\n"DEF, 2);
		ft_putstr_fd(RED"./so_long [name.ber]\n"DEF, 2);
		exit(EXIT_FAILURE);
	}
	file = av[1];
	game = malloc(sizeof(t_game));
	game_init(game);
	map_validator(game, file); // map is valid from this point onward
	get_map_image(game);
	game->win = mlx_new_window(game->ref, WIN_WIDTH, WIN_HEIGHT, "so_long");
	game->bg = xpm_to_image(game, BG, 0);
	return (game);
}

/**
 * 1. Start game
 * 2. Key hook (input_listener)
 * 3. render
 * 4. mlx_loop
**/
int	main(int ac, char **av)
{
	t_game	*game;

	game = start_game(ac, av);
	mlx_put_image_to_window(game->ref, game->win, game->bg->ref, 0, 0);
	mlx_put_image_to_window(game->ref, game->win, game->map_img->ref, 0, 0);
	mlx_loop(game->ref);
	return (0);
}
