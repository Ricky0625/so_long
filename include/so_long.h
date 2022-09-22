/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:24 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/22 13:21:26 by wricky-t         ###   ########.fr       */
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
# define FILE_EXT ".ber"
# define SPT_SIZE 64
# define GNAME "so_long: "

/** ==== KEYCODES ==== **/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

/** ==== UTILS STRUCTS ==== **/
/**
 * Vector - For size, location, index, area
**/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/**
 * Window - For mlx window
 * ref	: window instance pointer
 * size	: width & height of window
**/
typedef struct s_window
{
	void		*ref;
	t_vector	size;
}	t_window;

/**
 * Image metadata
 * 
 * The only two useful things are ref and size :D
 * The rest idk the actual usage of them, but they need
 * to be initialized for mlx to use if needed
**/
typedef struct s_image
{
	void		*ref;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
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

typedef enum e_tiletype
{
	PLAYER = 'P',
	FLOOR = '0',
	WALL = '1',
	VWALL = 'V',
	COLLECTIBLE = 'C',
	SKELETON = 'M',
	GHOST = 'G',
	EXIT = 'E'
}	t_tiletype;

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
typedef struct s_tile
{
	t_tiletype		type;
	t_tiletype		prev;
	t_vector		loc;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}	t_tile;

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

/** ==== MAIN STRUCTS ==== **/
/**
 * 
 * Vertical wall (entity)
 * 
 * Mostly will use this struct to animate the wall
**/
typedef struct s_vwall
{
	t_tile		*me;
	void		*idle1;
	void		*idle2;
	void		*idle3;
}	t_vwall;

/**
 * Struct for the special entity of the game, ghost or ghosy (not enemy)
 * 
 * show	: boolean. to appear or not
**/
typedef struct s_ghost
{
	int			show;
	t_tile		*me;
	t_image		*idle1;
	t_image		*idle2;
	t_image		*invisible;
	t_image		*appear;
}	t_ghost;

/**
 * Struct for the enemy of the game, skeleton or skely hehe
 * 
 * collide	: check if skeleton has collision with the wall
**/
typedef struct s_skeleton
{
	int			collide;
	t_tile		*me;
	t_image		*idle1;
	t_image		*idle2;
	t_image		*killed;
}	t_skeleton;

/**
 * The collectibles - no much special
 * 
 * It's just a struct to animate the collectibles
**/
typedef struct s_coll
{
	t_tile		*me;
	t_image		*idle1;
	t_image		*idle2;
}	t_coll;

typedef union u_entity_list
{
	t_skeleton	*skely;
	t_coll		*coll;
	t_vwall		*vwall;
}	t_entity_list;

/**
 * Info about the player
**/
typedef struct s_player
{
	int			moves;
	int			collected;
	t_tile		*me;
	t_image		*idle1;
	t_image		*idle2;
}	t_player;

/**
 * Basically everything the game needs to run
**/
typedef struct s_game
{
	void		*ref;
	t_window	window;
	t_map		map_data;
	t_tile		**tilemap;
	t_entity	entity;
	t_player	player;
	t_ghost		ghost;
	t_skeleton	*skeleton;
	t_coll		*collectibles;
	t_vwall		*vwall;
}	t_game;

/** ==== FUNCTION PROTOTYPES ==== **/

/** ==== INITIALIZATION & ITS UTILITIES ==== **/

/** ==== MAP PARSER & ITS UTILITIES& ITS UTILITIES==== **/
void	map_validator(t_game *game, char *file);
void	check_map_format(t_game *game);
void	is_rectangular(t_game *game);
void	get_entity(t_game *game, char ch);
int		find_entity(t_vector *loc, char **map, char entity);
char	**copy_map(t_game *game, char **map);
void	fill_map(t_vector *start, char **fill);
char	**add_aesthetic(t_game *game);
void	show_path(char **map);

/** ==== TILE MAP GENERATOR ==== **/

/** ==== RENDER ==== **/

/** ==== PLAYER MECHANISM ==== **/

/** ==== SKELETON MECHANISM ==== **/

/** ==== GHOST MECHANISM ==== **/

/** ==== ANIMATION ==== **/

/** ==== FREE ==== **/
void	free_map(char **map);
void	free_game(t_game *game);

#endif