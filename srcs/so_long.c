/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/22 16:13:02 by wricky-t         ###   ########.fr       */
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
	return (0);
}
