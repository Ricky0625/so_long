/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:15:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/25 17:28:44 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void    draw_corner_wall(t_game *game, int x, int y)
{
    t_image *map_img;
    t_image *wall;
    int     width;
    int     height;

    map_img = game->map_img;
    width = game->map_data.size.x;
    height = game->map_data.size.y;
    if (x == 0 && y == 0)
        wall = xpm_to_image(game, WALL_UL, 1);
    else if (x == 0 && y == width - 1)
        wall = xpm_to_image(game, WALL_UR, 1);
    else if (x == height - 1 && y == 0)
        wall = xpm_to_image(game, WALL_DL, 1);
    else if (x == height - 1 && y == width - 1)
        wall = xpm_to_image(game, WALL_DR, 1);
    else
        return ;
    copy_image(wall, map_img, y * SPT_SIZE, x * SPT_SIZE);
}