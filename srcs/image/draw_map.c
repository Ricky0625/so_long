/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/28 18:38:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	get_map_position(t_game *game, t_vector *pos)
{
	int	map_width;
	int	map_height;

	map_width = game->map_img->size.x;
	map_height = game->map_img->size.y;
	if (map_width <= WIN_WIDTH && map_height <= WIN_HEIGHT)
	{
		pos->x = (WIN_WIDTH - map_width) / 2;
		pos->y = (WIN_HEIGHT - map_height) / 2;
	}
}

void	draw_map(t_game *game)
{
	int	width;
	int	height;

	width = game->map_data.size.x * SPT_SIZE;
	height = game->map_data.size.y * SPT_SIZE;
	game->map_img = new_image(game, width, height, 1);
	draw_base(game);
	draw_entity(game);
}
