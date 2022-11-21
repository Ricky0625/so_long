/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:56:37 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/21 18:13:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	is_blk(char *buffer, int pixel)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if ((buffer[pixel + i] | 0x00) != 0x00)
			return (0);
	}
	return (1);
}

void	copy_pixel(t_data_addr *src, t_data_addr *dst)
{
	dst->buffer[dst->pixel + 0] = src->buffer[src->pixel + 0];
	dst->buffer[dst->pixel + 1] = src->buffer[src->pixel + 1];
	dst->buffer[dst->pixel + 2] = src->buffer[src->pixel + 2];
	dst->buffer[dst->pixel + 3] = src->buffer[src->pixel + 3];
}

/**
 * @brief Copy an image pixel by pixel onto another image.
 * 
 * src	: image source
 * dst	: image destination
 * x,y	: the coordinate of where source should be placed on destination
 */
// src and dst should fully initialized when passing in.
// This includes the image data address, size, void pointer to the image.
// x & y should always times the sprite size before passing in.
void	copy_image(t_image *src, t_image *dst, int x, int y)
{
	int	i;
	int	j;

	if (src == 0 || dst == 0)
		return ;
	j = -1;
	while (++j < src->size.y)
	{
		i = -1;
		while (++i < src->size.x)
		{
			src->data->pixel = (j * src->data->line_size) + (i * 4);
			dst->data->pixel = ((y + j) * dst->data->line_size) + ((x + i) * 4);
			if (!is_blk(src->data->buffer, src->data->pixel))
			{
				copy_pixel(src->data, dst->data);
			}
		}
	}
}

void	crop_image(t_image *src, t_image *dst, t_vector start)
{
	int	x;
	int	y;
	int	ori_start_y;

	x = -1;
	ori_start_y = start.y;
	while (++x < dst->size.y)
	{
		y = -1;
		start.y = ori_start_y;
		while (++y < dst->size.x)
		{
			src->data->pixel = (start.x * src->data->line_size) + (start.y * 4);
			dst->data->pixel = (x * dst->data->line_size) + (y * 4);
			copy_pixel(src->data, dst->data);
			start.y++;
		}
		start.x++;
	}
}
