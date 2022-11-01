/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/01 16:16:55 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief Close the game. The process when the user clicked on the red cross
 * 		  or pressed the 'ESC' key. This function will also free everything
 * 		  before exit to ensure there's no memory leaks.
 * 
 * @param game 
 * @return int. The return value is useless, it is required for the function
 * 		   that will be hooked on the mlx function/
 */
int	close_game(t_game *game)
{
	(void)game;
	exit(0);
	return (1);
}

/**
 * skeleton movement should be like update_animation. should be passed into loop hook
 * 
 * player movement:
 * 1. check if encounter a skeleton.
 * 		a. Need a function that takes in player location and check against the list
 * 		   of skeleton's location. If one matches, means player is dead. quit game.
 * 2. check if touch the wall, block, vwall
 * 		a. probably need a function to loop through the location of vwall, since it's a
 * 		   list. OR, just use method (b). since it's static item as well.
 * 		b. for static items like block and side walls, get the location of player, and 
 * 		   get the item on the map. If it's a '1' OR 'V' cannot pass.
 * 3. check if collected key
 * 		a. same logic as player movement (1).
 * 		b. when go pass a key, play effect animation and minus one on t_entity (collectible)
 * 		c. when t_entity.collectible == 0, play exit animation, clear set to 1. when player is on
 * 		   exit in this condition, player won the game. exit game.
 */
// the problem now is... it's very laggy
int	key_listener(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	else
		move_player(game, key);
	return (0);
}

/**
 * @brief Render everything to the screen.
 * 
 * Will start by clear up the screen. After that update each entity's animation
 * if any. Based on their current image, draw a map img. Place the background
 * img first then overlay the map img on it's top. Once the img is on the
 * screen, destroy the map img.
 * 
 * This will run in a loop. (mlx_loop_hook)
 */
int	render(t_game *game)
{
	mlx_clear_window(game->ref, game->win);
	update_animation(game);
	skeleton_roaming(game);
	check_if_skeletons_dead(game);
	draw_map(game);
	put_to_screen(game, &game->bg);
	put_to_screen(game, &game->final_img);
	return (1);
}

/**
 * @brief Initialize the t_game struct
 * 
 * @param game
 */
static void	game_init(t_game *game)
{
	game->ref = mlx_init();
	game->win = mlx_new_window(game->ref, WIN_WIDTH, WIN_HEIGHT, "so_long");
	entity_init(&game->entity);
	game->skeletons = NULL;
	game->collectibles = NULL;
	game->vwalls = NULL;
	game->map_img = NULL;
}

/**
 * @brief Initialize everything for the game to run
 * 
 * @param ac 
 * @param av 
 * @return t_game* (pointer to t_game), which will store all the things
 */
static t_game	*start_game(int ac, char **av)
{
	t_game	*game;
	char	*file;

	if (ac != 2)
	{
		ft_putstr_fd(RED "[ERROR]: Invalid Usage!\n" DEF, 2);
		ft_putstr_fd(RED "./so_long [name.ber]\n" DEF, 2);
		exit(EXIT_FAILURE);
	}
	file = av[1];
	game = malloc(sizeof(t_game));
	game_init(game);
	map_validator(game, file);
	fetch_all_imgs(game);
	update_entity(game);
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
	mlx_loop_hook(game->ref, render, game);
	mlx_key_hook(game->win, key_listener, game);
	mlx_hook(game->win, 17, 0L, close_game, game);
	mlx_loop(game->ref);
	return (0);
}
