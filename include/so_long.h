/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:24 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 19:41:02 by wricky-t         ###   ########.fr       */
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

// 64: 576 * 320
// 128: 1152 * 640
/** ==== MACROS ==== **/
# define WIN_WIDTH 1152
# define WIN_HEIGHT 640
# define FILE_EXT ".ber"
# define SPT_SIZE 128
# define APPEAR_MULTIPLIER 2
# define PATROL_COOLDOWN 60

/** ==== KEYCODES ==== **/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_SP 49
# define KEY_ESC 53

/** ==== KEYCODES (LINUX) ==== **/
// # define KEY_W 'w'
// # define KEY_A 'a'
// # define KEY_S 's'
// # define KEY_D 'd'
// # define KEY_SP 32
// # define KEY_ESC 65307

/** ==== UTILS ENUM ==== **/

/**
 * @brief A enum struct to represent entity
 */
typedef enum e_enty_type
{
	PLAYER = 'P',
	GHOST = 'G',
	SKELETON = 'M',
	COLLECTIBLE = 'C',
	VWALL = 'V',
	EXIT = 'E',
	WALL = '1'
}	t_enty_type;

/**
 * @brief A enum struct to represent the patrolling direction
 */
typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_DIRECTION,
	UNSET
}	t_direction;

/**
 * @brief A enum struct to represent the message status
 */
typedef enum e_msg_status
{
	SUCCESS,
	FAILURE,
	LOSE,
	QUIT,
	INVALID
}	t_msg_status;

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
	int		pixel;
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
	int		picker;
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
typedef struct s_img_db
{
	t_image	**player_idle_l;
	t_image	**player_idle_r;
	t_image	**ghost_idle;
	t_image	**ghost_appear;
	t_image	**ghost_boo;
	t_image	**key_idle;
	t_image	**skeleton_idle_l;
	t_image	**skeleton_idle_r;
	t_image	**skeleton_scared;
	t_image	**exit;
	t_image	**vwall_idle;
	t_image	**numbers;
	t_image	*corner_up_left;
	t_image	*corner_down_left;
	t_image	*corner_up_right;
	t_image	*corner_down_right;
	t_image	*side_up;
	t_image	*side_down;
	t_image	*side_left;
	t_image	*side_right;
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
	int			activate;
	t_vector	loc;
	t_anim		anim;
	t_anim		effect;
}	t_ghost;

/**
 * @brief Struct for the enemy of the game, skeleton or skely hehe
 *
 * @param killed	: if the skeleton has been killed
 * @param collide	: check if skeleton has collision with the wall
 * @param loc		: location
 * @param anim		: idle animation frame
 * @param prev		: previous roaming direction
 * @param move_dur	: like cooldown. for roaming
 * @param dir		: store can move to which direction
 */
typedef struct s_skeleton
{
	t_vector	loc;
	t_anim		anim;
	t_direction	dir;
	int			current_tick;
	int			surrounding[4];
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
	int			clear;
	t_anim		anim;
	t_vector	loc;
}	t_exit;

typedef struct s_img_put
{
	t_image		*img;
	t_vector	start_pixel;
	t_vector	start_index;
	t_vector	end_index;
	t_vector	on_screen_pos;
	int			is_big;
}	t_img_put;

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
	t_img_put	final;
	t_img_db	img_db;
}	t_game;

/** ==== FUNCTION PROTOTYPES ==== **/

/** ==== INITIALIZATION & ITS UTILITIES ==== **/
void		add_vwall(t_game *game, t_vector loc);
void		add_skeleton(t_game *game, t_vector loc);
void		add_collectible(t_game *game, t_vector loc);
void		add_ghost(t_game *game, t_vector loc);
void		add_player(t_game *game, t_vector loc);
void		add_exit(t_game *game, t_vector loc);
void		entity_init(t_entity *enty);
void		anim_init(t_anim *anim, int duration, t_image **frames);
void		vector_init(t_vector *vector);
void		set_vector(t_vector *vector, int x, int y);
int			is_same_vector(t_vector a, t_vector b);
void		map_data_init(t_map *map_data);

/** ==== MAP PARSER & ITS UTILITIES ==== **/
void		map_validator(t_game *game, char *file);
void		check_map_format(t_game *game);
void		check_if_rectangular(t_game *game);
void		get_entity(t_game *game, char ch);
char		**fill_map(t_game *game, t_vector start);
void		show_path(char **map);
char		**copy_map(t_game *game, char **map);
char		**add_aesthetic(t_game *game);
int			find_entity(t_vector *loc, char **map, char entity);
void		mapiteri(t_game *game, void (*draw)(t_game *, t_vector));

/** ==== IMAGE ==== **/
t_image		*xpm_to_image(t_game *game, char *file, int set_data);
t_image		*new_image(t_game *game, t_vector size, int set_data);
t_data_addr	*set_data_addr(t_image *img);
void		put_to_screen(t_game *game, t_img_put *img, int destroy);
void		draw_base(t_game *game, t_vector index);
void		draw_entity(t_game *game);
void		draw_map(t_game *game);
void		draw_ui(t_game *game);
void		copy_image(t_image *src, t_image *dst, int x, int y);
void		final_img_init(t_game *game);
void		fetch_all_imgs(t_game *game);

/** ==== MECHANISM ==== **/
void		move_player(t_game *game, int key);
int			detect_collision(t_game *game, t_vector dest, t_enty_type type);
void		skeleton_patrol(t_game *game);
void		check_if_skeletons_dead(t_game *game);
int			can_continue_patrolling(t_game *game, t_skeleton *skely);
t_vector	get_skely_dest(t_vector ori, int dir);

/** ==== ANIMATION ==== **/
void		update_animation(t_game *game);
void		update_entity(t_game *game);
void		update_frame(t_anim *anim);

/** ==== FREE ==== **/
void		free_map(char **map);
void		free_img(t_image *img);
void		exit_game(t_game *game, char *str, t_msg_status status);
int			close_game(t_game *game);

#endif