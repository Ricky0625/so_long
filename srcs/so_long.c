/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/14 12:52:11 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * TODO
 * 
 * Game Init
 * 1. Map parsing														[V]
 * 	  - check format													[V]
 * 		- check file name first											[V]
 *      - get raw map (unproccessed, a string)							[V]
 *    - get width, height												[V]
 * 	  - check map (Is it better to check using 2D array or a string)	[V]
 * 		- wall (Is it a rectangular shape)								[V]
 * 		- essential (1 Exit, 1 Collectible, 1 starting Position)		[V]
 * 		- Is there a valid path?										[V]
 *    - If all checking are fine, set game map							[V]
 * 2. Create a window													[V]
 * 	  - Create a window based on the width and height					[V]
 * 3. Put image (all the items)											[V]
 * 4. Mechanism
 * 	  - Player can walk
 * 	  - Player cannot pass through wall
 * 	  - Player can collect keys
 * 	  - When player touches skely, player died. game ends
 * 	  - When player collect all keys, exit door open
 * 	  EXTRA:
 * 	  - When player is beside (UDLR) ghost, ghost remind player
 * 		to press spacebar
 *    - When pressed spacebar, spawn another window?
 * 	  	- When this thing appears, player can type in numbers
 * 			- need to listen to the event
 * 		- Press enter to submit answer
 *    - If player manage to answer it, kill all skely.
 * 	  - If player cannot answer it, ghost dissappear.
 * 
 * Have a function that's dedicated to print error message and quit
 * ./so_long --help to show manual
 * Have a function to free the game upon exit
**/
int	main(int ac, char **av)
{
	t_game	*game;

	game = game_init(ac, av);
	window_init(game);
	player_init(game);
	place_map(game);
	print_surrounding(&game->player);
	show_path(game->map_data.map);
	mlx_key_hook(game->window.ref, input_listener, (void *)game);
	mlx_loop_hook(game->ref, update_frame, (void *)game);
	mlx_loop(game->ref);
	return (0);
}
