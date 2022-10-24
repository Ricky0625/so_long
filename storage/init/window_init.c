/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:59 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 20:44:43 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Close the window & free the memory
**/
int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}

/**
 * Set the size of the window
 * 
 * Get the number of col and rows of the map, times sprite size
**/
static void	set_window_size(t_game *game)
{
	int	width;
	int	height;

	width = game->map_data.size.x * SPT_SIZE;
	height = game->map_data.size.y * SPT_SIZE;
	game->window.size.x = width;
	game->window.size.y = height;
}

/**
 * Create a new window and set the properties.
 * Hook a closing event to the window as well.
**/
void	set_window(t_game *game)
{
	void	*mlx;
	void	*win_ptr;
	char	*name;

	mlx = game->ref;
	set_window_size(game);
	name = ft_strjoin(GNAME, game->map_data.file);
	win_ptr = mlx_new_window(
			mlx, game->window.size.x, game->window.size.y, name);
	game->window.ref = win_ptr;
	free(name);
}

/**
 * Set the properties of a window
**/
void	window_init(t_window *win)
{
	win->ref = 0;
	vector_init(&win->size);
}
