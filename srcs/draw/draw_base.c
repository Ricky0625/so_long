/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:15:32 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/21 18:13:47 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Get the base images, specially for image that belongs to layer i.
 * 		  Check the definition of layer i at the comment of draw_base().
 */
t_image	*get_base_img(t_game *game, int x, int y)
{
	t_vector	size;

	size = game->map_data.size;
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
void	draw_base(t_game *game, t_vector index)
{
	char		**map;
	t_image		*base;
	t_vector	pos;
	t_vector	map_size;

	map = game->map_data.map;
	if (map[index.x][index.y] == 'V')
		return ;
	pos = game->final.start_pixel;
	map_size = game->map_data.size;
	if (game->final.is_big == 0)
		set_vector(&pos, (index.y * SPT_SIZE) + pos.x,
			(index.x * SPT_SIZE) + pos.y);
	else
		set_vector(&pos,
			(index.y - game->final.start_index.y) * SPT_SIZE + pos.x,
			(index.x - game->final.start_index.x) * SPT_SIZE + pos.y);
	base = get_base_img(game, index.x, index.y);
	copy_image(base, game->final.img, pos.x, pos.y);
	if ((index.x > 0 && index.x < map_size.y - 1)
		&& (index.y > 0 && index.y < map_size.x - 1)
		&& map[index.x][index.y] == '1')
	{
		base = game->img_db.block;
		copy_image(base, game->final.img, pos.x, pos.y);
	}
}

void	print_mini(t_game *game, t_vector start, t_vector end)
{
	char	**map;
	int		ori_start_y;

	ori_start_y = start.y;
	map = game->map_data.map;
	while (start.x <= end.x)
	{
		start.y = ori_start_y;
		while (start.y <= end.y)
		{
			if (is_same_vector(game->player.loc, start))
				printf("P");
			else if (map[start.x][start.y] == 'P')
				printf("0");
			else
				printf("%c", map[start.x][start.y]);
			start.y++;
		}
		start.x++;
		printf("\n");
	}
	printf("\n");
}

/**
 * @brief Helper function to iterate through the map and run (draw *) on
 * 		  each of the character.
 */
void	mapiteri(t_game *game, void (*draw)(t_game *, t_vector))
{
	int			ori_start_y;
	t_vector	start;
	t_vector	end;

	start = game->final.start_index;
	end = game->final.end_index;
	ori_start_y = start.y;
	while (start.x <= end.x)
	{
		start.y = ori_start_y;
		while (start.y <= end.y)
		{
			draw(game, start);
			start.y++;
		}
		start.x++;
	}
}
