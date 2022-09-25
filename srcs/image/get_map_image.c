/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/25 17:25:07 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void    get_map_image(t_game *game)
{
    int     width;
    int     height;
    char    **map;

    width = game->map_data.size.x * SPT_SIZE;
    height = game->map_data.size.y * SPT_SIZE;
    game->map_img = new_image(game, width, height, 1);
    map = game->map_data.map;
    mapiteri(game, draw_corner_wall);
}