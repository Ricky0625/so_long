/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:29:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 13:48:12 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Free the 2D array map
 * 
 * Free each of the 1D array in 2D array
 * Free the pointer to 2D array at the end
**/
void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i] != NULL)
		free(map[i]);
	free(map);
}

/**
 * @brief Free the image
 * 
 * If the image pointer is already NULL, exit this function.
 * If the image data is set (mlx_set_data_addr), free the pointer to data addr
 * Free the image pointer at the end.
 */
void	free_img(t_image *img)
{
	if (img == NULL)
		return ;
	if (img->data != 0)
		free(img->data);
	free(img);
}
