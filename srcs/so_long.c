/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/15 20:18:40 by wricky-t         ###   ########.fr       */
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
	game->skeleton = 0;
	game->collectibles = 0;
	game->vwall = 0;
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
	// parse map here
	// generate tile map
	// set player
	// set ghost
	// get skeleton list
	// get vertical list
	// set window properties
	// place map based on tile map
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = start_game(ac, av);
	// listen to input
	// mlx_key_hook(game->window.ref, input_listener, (void *)game);
	
	// listen to exit event here
	// mlx_hook(game->window.ref, 17, 0, close_window, game);
	
	// update frame
	// mlx_loop_hook(game->ref, update_frame, (void *)game);

	// run game
	// mlx_loop(game->ref);
	return (0);
}
