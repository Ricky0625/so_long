/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:31:22 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 22:08:16 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Print the stats of the game upon exit (if needed)
 */
void	print_game_stats(t_game *game)
{
	ft_printf("Move count:\t");
	ft_printf(GN "%d\n" DEF, game->player.moves);
	ft_printf("Collected:\t");
	ft_printf(GN "%d/%d\n" DEF, game->player.collected, game->entity.coll);
	if (game->entity.ghost == 1 && game->entity.skely > 0
		&& game->ghost.activate == 0 && game->ghost.appear_counter != 0)
	{
		ft_printf(GN "%d " DEF, game->ghost.appear_counter);
		ft_printf("steps more on the GHOST's tile to activate the GHOST!\n");
	}
}

/**
 * @brief Exit the game and free stuffs
 * @param str: Message
 * @param status: the exit status
 */
void	exit_game(t_game *game, char *str, t_msg_status status)
{
	(void)game;
	if (status == SUCCESS)
		ft_printf(GN "CONGRATS! YOU WIN!\n" DEF);
	else if (status == FAILURE)
		ft_printf(RED "[ERROR]: %s\n" DEF, str);
	else if (status == WARNING)
	{
		ft_printf(YL "[WARNING]: %s\n" DEF, str);
		return ;
	}
	else if (status == LOSE)
		ft_printf(RED "Ahhh man. Try again next time.\n" DEF);
	else if (status == QUIT)
		ft_printf(GN "Thanks for playing!\n" DEF);
	if (status == SUCCESS || status == LOSE)
		print_game_stats(game);
	system("leaks -q so_long");
	if (status == SUCCESS)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

/**
 * @brief Close the game. The process when the user clicked on the red cross
 * 		  or pressed the 'ESC' key. This function will also free everything
 * 		  before exit to ensure there's no memory leaks.
 *
 * @param game
 * @return int. The return value is useless, it is required for the function
 * 		   that will be hooked on the mlx function
 */
int	close_game(t_game *game)
{
	(void)game;
	exit_game(game, NULL, QUIT);
	return (1);
}
