/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:16:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief Listen to the key pressed event and based on the key and do what
 * 		  the program suppose to do.
 * @param key: the key code of the key
 * @param game: the struct that stores everything
 * @return int. The return value is useless, it is required for the function
 * 		   that will be hooked on the mlx function
 */
static int	key_listener(int key, t_game *game)
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
 * 1. Clear the window so that we can place the new rendered image
 * 2. Update the animation of each entity, object
 * 3. Update the enemy patrol data. (If any)
 * 4. Check if the skeletons are dead, so that we can free the skeletons
 *    linked list.
 * 5. Draw the map. This includes the base of the map, all the objects and
 * 	  entities.
 * 6. Put the background image
 * 7. Put the map image (final, after cropped)
 * 8. Draw the user interface (player move count)
 *
 * This will run in a infinite loop. (mlx_loop_hook)
 */
static int	render(t_game *game)
{
	mlx_clear_window(game->ref, game->win);
	update_animation(game);
	skeleton_patrol(game);
	check_if_skeletons_dead(game);
	draw_map(game);
	put_to_screen(game, &game->bg);
	put_to_screen(game, &game->final_img);
	draw_ui(game);
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
		exit_game(NULL, "Invalid Usage!\n./so_long file.ber", FAILURE);
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
 * 2. Loop hook (render)
 * 3. Key hook (input_listener)
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
