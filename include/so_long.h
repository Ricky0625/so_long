/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:24 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/25 17:22:28 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib42/lib42.h"
# include "mlx.h"
# include <stdlib.h>

/** ==== TEXT STYLING ==== **/
# define RED "\033[0;31m"
# define YL "\033[0;33m"
# define GN "\033[0;32m"
# define DEF "\033[0m"

/** ==== MACROS ==== **/
# define WIN_WIDTH 1280
# define WIN_HEIGHT 896
# define FILE_EXT ".ber"
# define SPT_SIZE 128
# define GNAME "so_long: "

/** ==== KEYCODES ==== **/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3

/** ==== SPRITES ==== **/
# define PLAYER1 "assets/player/player1.xpm"
# define PLAYER2 "assets/player/player2.xpm"
# define SKELY1 "assets/skeleton/skeleton1.xpm"
# define SKELY2 "assets/skeleton/skeleton2.xpm"
# define GHOST1 "assets/ghost/ghost1.xpm"
# define GHOST2 "assets/ghost/ghost2.xpm"
# define GHOSTI1 "assets/ghost/ghost_i1.xpm"
# define KEY1 "assets/key/key1.xpm"
# define KEY2 "assets/key/key2.xpm"
# define WALL_U "assets/wall/wall_u.xpm"
# define WALL_D "assets/wall/wall_d.xpm"
# define WALL_L "assets/wall/wall_l.xpm"
# define WALL_R "assets/wall/wall_r.xpm"
# define WALL_UL "assets/wall/wall_ul.xpm"
# define WALL_UR "assets/wall/wall_ur.xpm"
# define WALL_DL "assets/wall/wall_dl.xpm"
# define WALL_DR "assets/wall/wall_dr.xpm"
# define VWALL1 "assets/vwall/vwall1.xpm"
# define VWALL2 "assets/vwall/vwall2.xpm"
# define VWALL3 "assets/vwall/vwall3.xpm"
# define FLOOR "assets/other/floor.xpm"
# define BLOCK "assets/other/block.xpm"
# define EXITO "assets/other/exit_open.xpm"
# define EXITC "assets/other/exit_close.xpm"
# define BG "assets/other/bg.xpm"

/** ==== UTILS STRUCTS ==== **/
/**
 * Vector - For size, location, index, area
**/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_data_addr
{
	char	*buffer;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_data_addr;

/**
 * Image metadata
 * 
 * ref				: pointer to the image
 * size				: image size
 * buffer			: memory address of the image
 * bits_per_pixel	: the number of pixels in a bit
 * line_size		: 
**/
typedef struct s_image
{
	void		*ref;
	t_vector	size;
	t_data_addr	*data;
}	t_image;

/**
 * Basically a summary of all the entities (how many of them)
 * Can use it for error checking.
**/
typedef struct s_entity
{
	int	plyr;
	int	coll;
	int	exit;
	int	skely;
	int	ghost;
}	t_entity;

/**
 * Tiletype enum
**/
// typedef enum e_tiletype
// {
// 	PLAYER = 'P',
// 	FLOOR = '0',
// 	WALL = '1',
// 	VWALL = 'V',
// 	COLLECTIBLE = 'C',
// 	SKELETON = 'M',
// 	GHOST = 'G',
// 	EXIT = 'E'
// }	t_tiletype;

/**
 * Tile - Info about a tile and its surrounding
 * 
 * type	: the type of the tile (check t_tiletype for more idea)
 * prev	: the previous type of the tile
 * loc	: location
 * up	: the tile above
 * down	: the tile below
 * left	: the tile on the left
 * right: the tile on the right
**/
// typedef struct s_tile
// {
// 	t_tiletype		type;
// 	t_tiletype		prev;
// 	t_vector		loc;
// 	struct s_tile	*up;
// 	struct s_tile	*down;
// 	struct s_tile	*left;
// 	struct s_tile	*right;
// }	t_tile;

/**
 * Info about the map
 * 
 * This is mostly used for the map parsing and error checking
 * before the map has been converted into tile map
 * 
 * raw	: raw map
 * map	: processed and validated map
 * file	: the name of the file
 * size	: the size of the map
**/
typedef struct s_map
{
	char		*raw;
	char		**map;
	char		*file;
	t_vector	size;
}	t_map;

/**
 * Struct for animation
 * 
 * current_tick	: to keep track when to change frame
 * duration		: the duration between each frame
 * num_of_frame	: number of frame
 * frames		: the animation frames
**/
typedef struct s_anim
{
	int		current_tick;
	int		duration;
	int		num_of_frame;
	void	**frames;
}	t_anim;

/** ==== MAIN STRUCTS ==== **/
/**
 * Vertical wall (entity)
 * 
 * Mostly will use this struct to animate the wall
 * loc	: location
 * idle	: idle animation
**/
typedef struct s_vwall
{
	t_vector	loc;
	t_anim		*idle;
}	t_vwall;

/**
 * Struct for the special entity of the game, ghost or ghosy (not enemy)
 * 
 * appear_counter	: pass by how many times to let ghost appear
 * loc				: location
 * idle				: idle animation
 * appear			: appear animation
**/
typedef struct s_ghost
{
	int			appear_counter;
	t_vector	loc;
	t_anim		*idle;
	t_anim		*appear;
}	t_ghost;

/**
 * Struct for the enemy of the game, skeleton or skely hehe
 * 
 * collide	: check if skeleton has collision with the wall
 * loc		: location
 * idle		: idle animation frame
 * killed	: killed animation frame
**/
typedef struct s_skeleton
{
	int			collide;
	t_vector	loc;
	t_anim		*idle;
	t_anim		*killed;
}	t_skeleton;

/**
 * The collectibles
 * 
 * collected: to check whether this item has been collected or not
 * loc		: location
 * idle		: the idle animation
 * effect	: the animation when player collects it
**/
typedef struct s_coll
{
	int			collected;
	t_vector	loc;
	t_anim		*idle;
	t_anim		*effect;
}	t_coll;

/**
 * Info about the player
 * 
 * moves	: how many moves
 * collected: collected how many collectible
 * loc		: location
 * idle		: idle animation
**/
typedef struct s_player
{
	int			moves;
	int			collected;
	t_vector	loc;
	t_anim		*idle;
}	t_player;

/**
 * Basically everything the game needs to run
 * 
 * ref			: mlx pointer
 * win			: mlx window pointer
 * map_dat		: map data
 * entity		: entity summary
 * player		: the player
 * ghost		: the ghost (only one)
 * skeleton		: skeleton list
 * collectibles	: collectible list
 * vwall		: vertical wall list
 * bg			: the background image
**/
typedef struct s_game
{
	void		*ref;
	void		*win;
	t_map		map_data;
	t_entity	entity;
	t_player	player;
	t_ghost		ghost;
	t_list		*skeleton;
	t_list		*collectibles;
	t_list		*vwall;
	t_image		*bg;
	t_image		*map_img;
}	t_game;

/** ==== FUNCTION PROTOTYPES ==== **/

/** ==== INITIALIZATION & ITS UTILITIES ==== **/
void	entity_init(t_entity *enty);
void	image_init(t_image *img, char *file, void *mlx);

/** ==== MAP PARSER & ITS UTILITIES ==== **/
void	map_validator(t_game *game, char *file);
void	check_map_format(t_game *game);
void	is_rectangular(t_game *game);
void	get_entity(t_game *game, char ch);
void	fill_map(t_vector *start, char **fill);
void	show_path(char **map);
char	**copy_map(t_game *game, char **map);
char	**add_aesthetic(t_game *game);
int		find_entity(t_vector *loc, char **map, char entity);
void	mapiteri(t_game *game, void (*f)(t_game *, int, int));

/** ==== IMAGE ==== **/
t_image		*xpm_to_image(t_game *game, char *file, int set_data);
t_image		*new_image(t_game *game, int width, int height, int set_data);
t_data_addr	*set_data_addr(t_image *img);
void		get_map_image(t_game *game);
void		copy_image(t_image *src, t_image *dst, int x, int y);
void    	draw_corner_wall(t_game *game, int x, int y);

/** ==== RENDER ==== **/

/** ==== PLAYER MECHANISM ==== **/

/** ==== SKELETON MECHANISM ==== **/

/** ==== GHOST MECHANISM ==== **/

/** ==== ANIMATION ==== **/

/** ==== FREE ==== **/
void	free_map(char **map);
void	free_game(t_game *game);

#endif