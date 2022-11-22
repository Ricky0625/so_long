/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:56:37 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 19:42:14 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if the pixel is a black pixel. As we know, black in RGB is
 * 		  (0, 0, 0). So, check if each of the value (RGB) is 0, if there's
 * 		  one that is not, meaning that it's not a black color. Hence, return
 * 		  0, else return 1.
 */
static int	is_blk(char *buffer, int pixel)
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
 * @brief Copy the pixel from destination to src. Basically to replace the
 * 	      pixel of src at [position] to the pixel of dst at [position].
 * 		  Since color is store in this way, RGBA / ABGR, we have to copy
 * 		  based on the order as well.
 */
static void	copy_pixel(t_data_addr *src, t_data_addr *dst)
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
