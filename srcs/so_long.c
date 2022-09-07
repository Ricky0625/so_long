/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/07 13:06:42 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * TODO
 * 
 * Game Init
 * 1. Map parsing
 * 	  - check format
 * 		- check file name first
 *      - get raw map (unproccessed, a string)
 *    - get width, height
 * 	  - check map (Is it better to check using 2D array or a string)
 * 		- wall (Is it a rectangular shape)
 * 		- essential (1 Exit, 1 Collectible, 1 starting Position)
 * 		- Is there a valid path?
 *    - If all checking are fine, set game map
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
	free_map(game->map_data.map);
	free(game);
	return (0);
}
