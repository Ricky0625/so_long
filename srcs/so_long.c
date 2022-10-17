/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 22:00:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	draw_map(game);
	mlx_put_image_to_window(game->ref, game->win, game->bg->ref, 0, 0);
	mlx_put_image_to_window(game->ref, game->win, game->final_img.img->ref, game->final_img.position.x, game->final_img.position.y);
	mlx_destroy_image(game->ref, game->final_img.img->ref);
	return (1);
}

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
	game->bg = xpm_to_image(game, BG, 1);
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
	mlx_hook(game->win, 17, 0L, close_game, game);
	mlx_loop(game->ref);
	return (0);
}
