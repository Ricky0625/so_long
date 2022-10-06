/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:15:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/06 15:05:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_image	*get_base_img(t_game *game, int x, int y)
{
	t_image		**corner;
	t_image		**side;
	t_vector	size;

	corner = game->img_db.corner_wall;
	side = game->img_db.side_wall;
	size = game->map_data.size;
	if (x == 0 && y == 0)
		return (corner[0]);
	else if (x == 0 && y == size.x - 1)
		return (corner[1]);
	else if (x == size.y - 1 && y == 0)
		return (corner[2]);
	else if (x == size.y - 1 && y == size.x - 1)
		return (corner[3]);
	else if (x == 0 && (y > 0 && y < size.x - 1))
		return (side[0]);
	else if (y == 0 && (x > 0 && x < size.y - 1))
		return (side[1]);
	else if (y == size.x - 1 && (x > 0 && x < size.y - 1))
		return (side[2]);
	else if (x == size.y - 1 && (y > 0 && y < size.x - 1))
		return (side[3]);
	return (game->img_db.floor);
}

/**
 * Draw the base of the map to the map image
 * 
 * The base of the map are: The walls and the floor
**/
void	draw_base(t_game *game)
{
	int		x;
	int		y;
	char	**map;
	t_image	*base;

	x = -1;
	map = game->map_data.map;
	while (map[++x] != NULL)
	{
		y = -1;
		while (map[x][++y] != '\0')
		{
			base = get_base_img(game, x, y);
			copy_image(base, game->map_img, y * SPT_SIZE, x * SPT_SIZE);
		}
	}
}

void	draw_entity(t_game *game)
{
	lstiteri(game, &game->vwalls, draw_vertical_wall);
	lstiteri(game, &game->skeletons, draw_skeletons);
	lstiteri(game, &game->collectibles, draw_colls);
	draw_player(game);
	if (game->entity.ghost == 1)
		draw_ghost(game);
}
