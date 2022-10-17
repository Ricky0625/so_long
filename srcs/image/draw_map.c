/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 16:47:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	draw_map(t_game *game)
{
	t_vector	size;

	size = game->map_data.size;
	size.x *= SPT_SIZE;
	size.y *= SPT_SIZE;
	game->map_img = new_image(game, size, 1);
	mapiteri(game, draw_base);
	draw_entity(game);
}
