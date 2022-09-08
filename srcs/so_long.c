/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/08 14:13:37 by wricky-t         ###   ########.fr       */
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
 * 2. Create a window
 * 	  - Create a window based on the width and height
 * 3. Put image
 *    - put dummy image first
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
	mlx_loop(game->ref);
	return (0);
}
