/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 21:11:50 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initialize the game, basically everything
**/
static void	game_init(t_game *game)
{
	game->ref = mlx_init();
	window_init(&game->window);
	map_init(&game->map_data);
	entity_init(&game->entity);
	player_init(&game->player);
	ghost_init(&game->ghost);
	game->tilemap = NULL;
	game->skeleton = NULL;
	game->collectibles = NULL;
	game->vwall = NULL;
}

/**
 * Start the game
 * 
 * 1. Initialize game
 * 2. Parse map
 * 3. Generate tile map
 * 4. Update player info
 * 5. Update ghost info
 * 6. Get skeleton (enemy) list
 * 7. Get vertical wall list
 * 8. Set window properties
 * 9. Place the map onto the window
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
	map_validator(game, file);
	tilemap_generator(game);
	player_update(game);
	ghost_update(game);
	skeleton_update(game);
	collectible_update(game);
	vwall_update(game);
	set_window(game);
	// place map based on tile map
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = start_game(ac, av);
	// mlx_key_hook(game->window.ref, input_listener, (void *)game);
	mlx_hook(game->window.ref, 17, 0, close_window, game);
	// mlx_loop_hook(game->ref, update_frame, (void *)game);
	mlx_loop(game->ref);
	return (0);
}
