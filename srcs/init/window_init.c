/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:59 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 14:41:43 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	set_window_size(t_game *game)
{
	int	width;
	int	height;

	width = game->map_data.size.x * SPT_SIZE;
	height = game->map_data.size.y * SPT_SIZE;
	game->window.size.x = width;
	game->window.size.y = height;
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
}

void	new_window(t_game *game)
{
	void	*mlx;
	void	*win_ptr;
	char	*name;

	mlx = game->ref;
	name = ft_strjoin(GNAME, game->map_data.file);
	win_ptr = mlx_new_window(
			mlx, game->window.size.x, game->window.size.y, name);
	game->window.ref = win_ptr;
	mlx_hook(game->window.ref, 17, 0, close_window, game);
	free(name);
}

void	window_init(t_game *game)
{
	set_window_size(game);
	new_window(game);
}
