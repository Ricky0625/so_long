/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:15:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 17:42:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Get the base images, specially for image that belongs to layer i.
 * 		  Check the definition of layer i at the comment of draw_base().
 */
t_image	*get_base_img(t_game *game, int x, int y, t_vector size)
{
	char	**map;

	map = game->map_data.map;
	if (x == 0 && y == 0)
		return (game->img_db.corner_up_left);
	else if (x == 0 && y == size.x - 1)
		return (game->img_db.corner_up_right);
	else if (x == size.y - 1 && y == 0)
		return (game->img_db.corner_down_left);
	else if (x == size.y - 1 && y == size.x - 1)
		return (game->img_db.corner_down_right);
	else if (x == 0 && (y > 0 && y < size.x - 1))
		return (game->img_db.side_up);
	else if (y == 0 && (x > 0 && x < size.y - 1))
		return (game->img_db.side_left);
	else if (y == size.x - 1 && (x > 0 && x < size.y - 1))
		return (game->img_db.side_right);
	else if (x == size.y - 1 && (y > 0 && y < size.x - 1))
		return (game->img_db.side_down);
	return (game->img_db.floor);
}

/**
 * @brief Draw the base of the map. Basically anything that are static, will not
 * 		  move when the game is running. This includes the floor, block, & the 
 * 		  wall (except vertical wall).
 * 		  Base consists of two layer:
 *        i.	The wall and floor (below)
 *        ii.	Block (above, overlay)
 * 		  Layer i will be drawn onto the screen first then the blocks.
 * 		  There's a special checking condition. If the character is a vertical
 *   	  wall ('V'), skip this. The reason is that, if i don't do that, the
 * 		  location of that vertical wall will be replaced by the floor. After
 * 		  that when drawing the vertical wall, we will replace the whole image
 * 		  to vertical wall again. So, the drawing here is unecessary.
 */
void	draw_base(t_game *game, int x, int y)
{
	char		**map;
	t_vector	map_size;
	t_image		*base;
	t_image		*block;

	map = game->map_data.map;	
	map_size = game->map_data.size;
	if (map[x][y] == 'V')
		return ;
	base = get_base_img(game, x, y, map_size);
	block = game->img_db.block;
	copy_image(base, game->map_img, y * SPT_SIZE, x * SPT_SIZE);
	if ((x > 0 && x < map_size.y - 1) && (y > 0 && y < map_size.x - 1)
		&& map[x][y] == '1')
		copy_image(block, game->map_img, y * SPT_SIZE, x * SPT_SIZE);
}

/**
 * @brief Helper function to iterate through the map and run (fun *) on
 * 		  each of the character.
 */
void	mapiteri(t_game *game, void (*fun)(t_game *, int, int))
{
	char 	**map;
	int		x;
	int		y;

	map = game->map_data.map;
	x = -1;
	while (map[++x] != NULL)
	{
		y = -1;
		while (map[x][++y] != '\0')
			fun(game, x, y);
	}
}