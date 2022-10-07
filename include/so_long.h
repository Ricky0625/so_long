/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:24 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/06 20:01:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib42/lib42.h"
# include "../assets/sprites.h"
# include "mlx.h"
# include <stdlib.h>

/** ==== TEXT STYLING ==== **/
# define RED "\033[0;31m"
# define YL "\033[0;33m"
# define GN "\033[0;32m"
# define DEF "\033[0m"

/** ==== MACROS ==== **/
# define WIN_WIDTH 1152
# define WIN_HEIGHT 640
# define FILE_EXT ".ber"
# define SPT_SIZE 128
# define GNAME "so_long: "

/** ==== KEYCODES ==== **/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3

/** ==== UTILS STRUCTS ==== **/

/**
 * @brief Vector - For size, location, index, area
**/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/**
 * @brief Image data address
 */
typedef struct s_data_addr
{
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_data_addr;

/**
 * @brief Image metadata
 * 
 * @param ref			: pointer to the image
 * @param size			: image size
 * @param buffer		: memory address of the image
 * @param bits_per_pixel: the number of pixels in a bit
 * @param line_size		: 
**/
typedef struct s_image
{
	void		*ref;
	t_vector	size;
	t_data_addr	*data;
}	t_image;

/**
 * @brief Basically a summary of all the entities (how many of them)
 * Can use it for error checking.
 */
typedef struct s_entity
{
	int	plyr;
	int	coll;
	int	exit;
	int	skely;
	int	ghost;
}	t_entity;

/**
 * @brief Info about the map
 * 
 * This is mostly used for the map parsing and error checking
 * before the map has been converted into tile map
 * 
 * @param raw	: raw map
 * @param map	: processed and validated map
 * @param file	: the name of the file
 * @param size	: the size of the map
 */
typedef struct s_map
{
	char		*raw;
	char		**map;
	char		*file;
	t_vector	size;
}	t_map;

/**
 * @brief Struct for animation
 * 
 * @param current_tick	: to keep track when to change frame
 * @param duration		: the duration between each frame
 * @param num_of_frame	: number of frame (total frame)
 * @param frames		: the animation frames
 */
typedef struct s_anim
{
	int		current_tick;
	int		duration;
	int		current_frame;
	t_image	**frames;
}	t_anim;

/**
 * @brief A "database" for the images
 * 
 * @details Each of the struct member is an array of struct type t_image.
 * This will be initialized before generating the maps.
 * The idea is that since the program will be hooked on a mlx_loop_hook
 * to render next frame, it's not recommended to xpm_to_image everytime
 * because it will cost a lot of memory. And since all these are constant,
 * they should be initialized once only. When needed, just point to the
 * array and get the image inside.
 */
typedef struct s_img_db {
	t_image	**player_idle;
	t_image	**ghost_idle;
	t_image	**ghost_appear;
	t_image	**ghost_cutscene;
	t_image	**key_idle;
	t_image	**key_effect;
	t_image	**skeleton_idle;
	t_image	**skeleton_killed;
	t_image	**exit;
	t_image	**vwall_idle;
	t_image	**corner_wall;
	t_image	**side_wall;
	t_image	*floor;
	t_image	*block;
}	t_img_db;

/**
 * @brief Vertical wall (entity)
 * 
 * Mostly will use this struct to animate the wall
 * @param loc	: location
 * @param anim	: idle animation
 */
typedef struct s_vwall
{
	t_vector	loc;
	t_anim		anim;
}	t_vwall;

/**
 * @brief Struct for the special entity of the game, ghost or ghosy (not enemy)
 * 
 * @param appear_counter: pass by how many times to let ghost appear
 * @param loc			: location
 * @param anim			: idle/appearing animation
 */
typedef struct s_ghost
{
	int			appear_counter;
	t_vector	loc;
	t_anim		anim;
}	t_ghost;

/**
 * @brief Struct for the enemy of the game, skeleton or skely hehe
 * 
 * @param collide	: check if skeleton has collision with the wall
 * @param loc		: location
 * @param idle		: idle animation frame
 * @param killed	: killed animation frame
 */
typedef struct s_skeleton
{
	int			collide;
	t_vector	loc;
	t_anim		anim;
}	t_skeleton;

/**
 * @brief The collectibles
 * 
 * @param collected	: to check whether this item has been collected or not
 * @param loc		: location
 * @param idle		: the idle animation
 * @param effect	: the animation when player collects it
 */
typedef struct s_coll
{
	int			collected;
	t_vector	loc;
	t_anim		anim;
}	t_coll;

/**
 * @brief Info about the player
 * 
 * @param moves		: how many moves
 * @param collected	: collected how many collectible
 * @param loc		: location
 * @param idle		: idle animation
 */
typedef struct s_player
{
	int			moves;
	int			collected;
	t_vector	loc;
	t_anim		anim;
}	t_player;

/**
 * @brief Struct for the exit
 * 
 * @param clear	: check if the player clear the stage or not
 * @param anim	: animation for exit open
 */
typedef struct s_exit
{
	int		clear;
	t_anim	anim;
}	t_exit;

/**
 * @brief Basically everything the game needs to run
 *
 * @param ref			: mlx pointer
 * @param win			: mlx window pointer
 * @param map_data		: map data
 * @param entity		: entity summary
 * @param player		: the player
 * @param ghost			: the ghost (only one)
 * @param exit			: the exit (only one)
 * @param skeleton		: skeleton list
 * @param collectibles	: collectible list
 * @param vwall			: vertical wall list
 * @param bg			: the background image
 * @param imgdb			: the image database
 */
typedef struct s_game
{
	void		*ref;
	void		*win;
	t_map		map_data;
	t_entity	entity;
	t_player	player;
	t_ghost		ghost;
	t_exit		exit;
	t_list		*skeletons;
	t_list		*collectibles;
	t_list		*vwalls;
	t_image		*bg;
	t_image		*map_img;
	t_img_db	img_db;
}	t_game;

/**
 * @brief A enum struct to represent entity
 */
typedef enum e_enty_type
{
	PLAYER = 'P',
	GHOST = 'G',
	SKELETON = 'M',
	COLLECTIBLE = 'C',
	VWALL = 'V'
}	t_enty_type;

/** ==== FUNCTION PROTOTYPES ==== **/

/** ==== INITIALIZATION & ITS UTILITIES ==== **/
void		add_vwall(t_game *game, t_vector loc);
void		add_skeleton(t_game *game, t_vector loc);
void		add_collectible(t_game *game, t_vector loc);
void		add_ghost(t_game *game, t_vector loc);
void		add_player(t_game *game, t_vector loc);
void		entity_init(t_entity *enty);
void		anim_init(t_anim *anim, int duration, t_image **frames);
void		vector_init(t_vector *vector);
void		set_vector(t_vector *vector, int x, int y);

/** ==== MAP PARSER & ITS UTILITIES ==== **/
void		map_validator(t_game *game, char *file);
void		check_map_format(t_game *game);
void		is_rectangular(t_game *game);
void		get_entity(t_game *game, char ch);
void		fill_map(t_vector *start, char **fill);
void		show_path(char **map);
char		**copy_map(t_game *game, char **map);
char		**add_aesthetic(t_game *game);
int			find_entity(t_vector *loc, char **map, char entity);
void		mapiteri(t_game *game, void (*f)(t_game *, int, int));

/** ==== IMAGE ==== **/
t_image		*xpm_to_image(t_game *game, char *file, int set_data);
t_image		*new_image(t_game *game, t_vector size, int set_data);
t_data_addr	*set_data_addr(t_image *img);
void		draw_map(t_game *game);
void		copy_image(t_image *src, t_image *dst, int x, int y);
void		draw_base(t_game *game);
void		lstiteri(t_game *game, t_list **lst,
				void (*f)(t_game *game, void *));
void		draw_vertical_wall(t_game *game, void *content);
void		draw_skeletons(t_game *game, void *content);
void		draw_colls(t_game *game, void *content);
void		draw_player(t_game *game);
void		draw_ghost(t_game *game);
void		draw_entity(t_game *game);

void		fetch_all_imgs(t_game *game);

/** ==== RENDER ==== **/

/** ==== PLAYER MECHANISM ==== **/

/** ==== SKELETON MECHANISM ==== **/

/** ==== GHOST MECHANISM ==== **/

/** ==== ANIMATION ==== **/
void		update_animation(t_game *game);
void		update_entity(t_game *game);

/** ==== FREE ==== **/
void		free_map(char **map);
void		free_game(t_game *game);

#endif