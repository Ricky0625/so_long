/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:42:54 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/20 21:05:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_data_addr	*set_data_addr(t_image *img)
{
	t_data_addr	*data;

	data = malloc(sizeof(t_data_addr));
	data->buffer = mlx_get_data_addr(img->ref, &data->bits_per_pixel,
			&data->line_size, &data->endian);
	data->pixel = 0;
	return (data);
}

t_image	*new_image(t_game *game, t_vector size, int set_data)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	img->ref = mlx_new_image(game->ref, size.x, size.y);
	img->size = size;
	if (set_data == 1)
		img->data = set_data_addr(img);
	else
		img->data = 0;
	return (img);
}

t_image	*xpm_to_image(t_game *game, char *file, int set_data)
{
	t_image		*img;

	img = malloc(sizeof(t_image));
	img->ref = mlx_xpm_file_to_image(game->ref, file,
			&img->size.x, &img->size.y);
	if (set_data == 1)
		img->data = set_data_addr(img);
	else
		img->data = 0;
	return (img);
}

/**
 * @brief Put image onto the screen. Destroy the image afterward
 * 		  to prevent the img to stack onto each other in a loop.
 */
void	put_to_screen(t_game *game, t_img_put *img)
{
	t_vector	pos;

	pos = img->position;
	mlx_put_image_to_window(game->ref, game->win, img->img->ref, pos.y, pos.x);
	mlx_destroy_image(game->ref, img->img->ref);
}
