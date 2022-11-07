/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 19:03:16 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Draw the map based on the 
 */
void	draw_map(t_game *game)
{
	t_vector	size;

	size = game->map_data.size;
	set_vector(&size, size.x * SPT_SIZE, size.y * SPT_SIZE);
	if (game->map_img != NULL)
		free_img(game->map_img);
	game->map_img = new_image(game, size, 1);
	mapiteri(game, draw_base);
	draw_entity(game);
	final_img_init(game);
}

/**
 * @brief Check if the map is a big map or not. The definition of big map
 * 		  here refers to the maps that are either:
 * 		  1. Horizontally & vertically
 * 		  2. Horizontally
 * 		  3. Vertically
 */
int	is_big_map(t_game *game)
{
	t_vector	map_size;

	map_size = game->map_data.size;
	set_vector(&map_size, map_size.x * SPT_SIZE, map_size.y * SPT_SIZE);
	return ((map_size.x > WIN_WIDTH && map_size.y > WIN_HEIGHT)
		|| (map_size.x >= WIN_WIDTH && map_size.y < WIN_HEIGHT)
		|| (map_size.x < WIN_WIDTH && map_size.y >= WIN_HEIGHT));
}

void	set_final_size(t_game *game, t_vector *start, t_vector end)
{
	int			map_width;
	int			map_height;
	t_vector	final_size;

	map_width = game->map_data.size.x;
	map_height = game->map_data.size.y;
	if (start->y < 0)
		start->y = 0;
	if (start->x < 0)
		start->x = 0;
	if (end.x > map_height - 1)
		end.x = map_height - 1;
	if (end.y > map_width - 1)
		end.y = map_width - 1;
	set_vector(&final_size,
		(end.y - start->y + 1) * SPT_SIZE, (end.x - start->x + 1) * SPT_SIZE);
	if (game->final_img.img != NULL)
		free_img(game->final_img.img);
	game->final_img.img = new_image(game, final_size, 1);
}

void	set_crop_point(t_vector ply_loc, t_vector *start, t_vector *end)
{
	t_vector	padding;

	set_vector(&padding,
		(WIN_WIDTH / SPT_SIZE - 1) / 2, (WIN_HEIGHT / SPT_SIZE - 1) / 2);
	set_vector(start, ply_loc.x - padding.y, ply_loc.y - padding.x);
	set_vector(end, ply_loc.x + padding.y, ply_loc.y + padding.x);
}

// check start point will be suffcient
// seems to be working
// horizontal & vertical has problem
void	set_on_screen_position(t_game *game, t_vector start)
{
	t_vector	*final_pos;
	int			pos_x;
	int			pos_y;

	final_pos = &game->final_img.position;
	pos_x = 0;
	pos_y = 0;
	if (start.x < 0)
		pos_x = -start.x;
	if (start.y < 0)
		pos_y = -start.y;
	set_vector(final_pos, pos_x * SPT_SIZE, pos_y * SPT_SIZE);
}

/**
 * Process:
 * 
 * 1. Set crop point (not calibrate yet, might have negative indice)
 * 2. Set final img on screen position
 * 3. Re-calibrate
 * 3. Set final img size
 * 4. Crop image
 */
void	get_final_img(t_game *game)
{
	t_vector	start;
	t_vector	end;

	set_crop_point(game->player.loc, &start, &end);
	set_on_screen_position(game, start);
	set_final_size(game, &start, end);
	set_vector(&start, start.x * SPT_SIZE, start.y * SPT_SIZE);
	crop_image(game->map_img, game->final_img.img, start);
}

/**
* Create final img
* 
* Need a while loop to iterate through that will act as the index
* of the screen.
* Need to check if the (index + 1) * 128 will not exceed the screen
* When (x + 1) * 128 >= WIN_HEIGHT && (y + 1) * 128 >= WIN_WIDTH,
* exit the loop.
* 
* Need another set of index system to iterate through the map_img
* When one or two of the indice is negative, OR out of the 
* width & height of the map, ignore it. It probably
* means it's out of the map.
* @todo maybe the image size is too big, which cause the whole thing to be laggy
*/
void	final_img_init(t_game *game)
{
	t_img_put	*final;
	t_vector	map_size;

	final = &game->final_img;
	map_size = game->map_data.size;
	set_vector(&map_size, map_size.x * SPT_SIZE, map_size.y * SPT_SIZE);
	vector_init(&final->position);
	if (is_big_map(game) == 1)
		get_final_img(game);
	else
	{
		final->img = game->map_img;
		set_vector(&final->position, (WIN_HEIGHT - map_size.y) / 2,
			(WIN_WIDTH - map_size.x) / 2);
	}
	draw_ui(game);
}
