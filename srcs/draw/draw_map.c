/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:42:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/16 19:38:11 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

// void	set_final_size(t_game *game, t_vector *start, t_vector end)
// {
// 	int			map_width;
// 	int			map_height;
// 	t_vector	final_size;

// 	map_width = game->map_data.size.x;
// 	map_height = game->map_data.size.y;
// 	if (start->y < 0)
// 		start->y = 0;
// 	if (start->x < 0)
// 		start->x = 0;
// 	if (end.x > map_height - 1)
// 		end.x = map_height - 1;
// 	if (end.y > map_width - 1)
// 		end.y = map_width - 1;
// 	set_vector(&final_size,
// 		(end.y - start->y + 1) * SPT_SIZE, (end.x - start->x + 1) * SPT_SIZE);
// 	// if (game->final_img.img != NULL)
// 		// free_img(game->final_img.img);
// 	// game->final_img.img = new_image(game, final_size, 1);
// }

// check start point will be suffcient
// seems to be working
// horizontal & vertical has problem
// void	set_on_screen_position(t_game *game, t_vector start)
// {
// 	t_vector	*final_pos;
// 	int			pos_x;
// 	int			pos_y;

// 	// final_pos = &game->final_img.position;
// 	pos_x = 0;
// 	pos_y = 0;
// 	if (start.x < 0)
// 		pos_x = -start.x;
// 	if (start.y < 0)
// 		pos_y = -start.y;
// 	set_vector(final_pos, pos_x * SPT_SIZE, pos_y * SPT_SIZE);
// }

/**
 * Process:
 * 
 * 1. Set crop point (not calibrate yet, might have negative indice)
 * 2. Set final img on screen position
 * 3. Re-calibrate
 * 3. Set final img size
 * 4. Crop image
 */
// void	get_final_img(t_game *game)
// {
// 	t_vector	start;
// 	t_vector	end;

// 	set_crop_point(game->player.loc, &start, &end);
// 	// set_on_screen_position(game, start);
// 	set_final_size(game, &start, end);
// 	set_vector(&start, start.x * SPT_SIZE, start.y * SPT_SIZE);
// 	// crop_image(game->map_img, game->final_img.img, start);
// }

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
// void	final_img_init(t_game *game)
// {
// 	// t_img_put	*final;
// 	t_vector	map_size;

// 	// final = &game->final_img;
// 	map_size = game->map_data.size;
// 	set_vector(&map_size, map_size.x * SPT_SIZE, map_size.y * SPT_SIZE);
// 	vector_init(&game->final.position);
// 	if (is_big_map(game) == 1)
// 		get_final_img(game);
// 	else
// 	{
// 		// final->img = game->map_img;
// 		printf("hello\n");
// 		// set_vector(&game->final.position, (WIN_HEIGHT - map_size.y) / 2,
// 			// (WIN_WIDTH - map_size.x) / 2);
// 		int x = game->final.position.x; // dst pos
// 		int y = game->final.position.y; // dst pos
// 		int i = -1; // src pos
// 		int j = -1; // src pos
// while (++i < game->map_img->size.y)
// {
// 	j = -1;
// 	while (++j < game->map_img->size.x)
// 	{
// 		game->final.img->data->pixel =
		// 		(x + i) * game->final.img->data->line_size + (y + j) * 4;
// 		game->map_img->data->pixel =
				// (i * game->map_img->data->line_size) + (j * 4);
// 		if (!is_blk(game->map_img->data->buffer, game->map_img->data->pixel))
// 			copy_pixel(game->map_img->data, game->final.img->data);
// 	}
// }
// 	}
// }

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
		|| (map_size.x > WIN_WIDTH && map_size.y <= WIN_HEIGHT)
		|| (map_size.x <= WIN_WIDTH && map_size.y > WIN_HEIGHT));
}

void	set_crop_point(t_vector ply_loc, t_vector *start, t_vector *end)
{
	t_vector	padding;

	set_vector(&padding,
		(WIN_WIDTH / SPT_SIZE - 1) / 2, (WIN_HEIGHT / SPT_SIZE - 1) / 2);
	set_vector(start, ply_loc.x - padding.y, ply_loc.y - padding.x);
	set_vector(end, ply_loc.x + padding.y, ply_loc.y + padding.x);
}

// copy from 0,0 to end of the map
void	draw_small(t_game *game)
{
	t_vector	*start;
	t_vector	*end;
	t_vector	*dst_pos;

	start = &game->final.start_index;
	end = &game->final.end_index;
	dst_pos = &game->final.start_pixel; 
	vector_init(start);
	set_vector(end, game->map_data.size.y - 1, game-> map_data.size.x - 1);
	set_vector(dst_pos, (WIN_WIDTH - game->map_data.size.x * SPT_SIZE) / 2,
		(WIN_HEIGHT - game->map_data.size.y * SPT_SIZE) / 2);
	mapiteri(game, draw_base);
	draw_entity(game);
}

/**
 * @brief Draw the map based on the map
 */
// big map:// copy a certain part of the map, sometimes it will be pasted
// at 0,0 or others,
// depends on where is the player
void	draw_map(t_game *game)
{
	if (game->final.img != NULL)
		free_img(game->final.img);
	game->final.img = xpm_to_image(game, BG, 1);
	vector_init(&game->final.on_screen_pos);
	if (is_big_map(game) == 1)
		printf("big map\n");
	else
		draw_small(game);
	draw_ui(game);
}
