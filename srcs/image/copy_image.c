/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:56:37 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 15:15:04 by wricky-t         ###   ########.fr       */
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

/**
 * Copy an image pixel by pixel onto another image.
 * 
 * src	: image source
 * dst	: image destination
 * x,y	: the coordinate of where source should be placed on destination
**/
// src and dst should fully initialized when passing in.
// This includes the image data address, size, void pointer to the image.
// x & y should always times the sprite size before passing in.
void	copy_image(t_image *src, t_image *dst, int x, int y)
{
	int	i;
	int	j;
	int	src_pixel;
	int	dst_pixel;

	if (src == 0 || dst == 0)
		return ;
	j = -1;
	while (++j < src->size.y)
	{
		i = -1;
		while (++i < src->size.x)
		{
			src_pixel = (j * src->data->line_size) + (i * 4);
			dst_pixel = ((y + j) * dst->data->line_size) + ((x + i) * 4);
			if (!is_blk(src->data->buffer, src_pixel))
			{
				dst->data->buffer[dst_pixel + 0] = src->data->buffer[src_pixel + 0];
				dst->data->buffer[dst_pixel + 1] = src->data->buffer[src_pixel + 1];
				dst->data->buffer[dst_pixel + 2] = src->data->buffer[src_pixel + 2];
				dst->data->buffer[dst_pixel + 3] = src->data->buffer[src_pixel + 3];
			}
		}
	}
}
