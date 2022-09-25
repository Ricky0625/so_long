/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:42:54 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/25 16:58:58 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_data_addr	*set_data_addr(t_image *img)
{
	t_data_addr *data;

	data = malloc(sizeof(t_data_addr));
	data->buffer = mlx_get_data_addr(img->ref, &data->bits_per_pixel,
			&data->line_size, &data->endian);
	return (data);
}

t_image	*new_image(t_game *game, int width, int height, int set_data)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	img->ref = mlx_new_image(game->ref, width, height);
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
