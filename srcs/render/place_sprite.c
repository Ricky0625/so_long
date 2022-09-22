/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:11:12 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/20 16:15:11 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	place_sprite(t_game *game, char *sprite, int x, int y)
{
	t_image		img;
	t_vector	loc;

	image_init(&img);
	img.ref = mlx_xpm_file_to_image(game->ref, sprite, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ref, &img.bits_per_pixel,
		&img.line_size, &img.endian);
	mlx_put_image_to_window(game->ref, game->window.ref, img.ref, x, y);
	mlx_destroy_image(game->ref, img.ref);
}
