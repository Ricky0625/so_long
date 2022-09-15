/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_new.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:46:24 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/15 16:23:27 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib42/lib42.h"
# include "mlx.h"

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
 * Vector - For size, location, index, area
**/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

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
	GHOST = 'G'
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
	t_tiletype	type;
	t_tiletype	prev;
	t_vector	loc;
	t_tile		*up;
	t_tile		*down;
	t_tile		*left;
	t_tile		*right;
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
	t_vector	loc;
	t_image		*idle1;
	t_image		*idle2;
	t_image		*idle3;
}	t_vwall;

typedef struct s_ghost
{
	int			show;
	t_tile		me;
	t_image		*idle1;
	t_image		*idle2;
	t_image		*invisible;
	t_image		*appear;
}	t_ghost;

typedef struct s_skeleton
{
	int			collide;
	t_tile		me;
	t_image		*idle1;
	t_image		*idle2;
	t_image		*killed;
}	t_skeleton;

typedef struct s_coll
{
	t_tile		me;
	t_image		*idle1;
	t_image		*idle2;
}	t_coll;

typedef struct s_player
{
	int			moves;
	int			collected;
	t_tile		me;
	t_image		*idle1;
	t_image		*idle2;
}	t_player;

typedef struct s_game
{
	void		*ref;
	t_window	window;
	t_map		map_data;
	t_entity	entity;
	t_player	player;
	t_ghost		ghost;
	t_skeleton	*skeleton;
	t_coll		*collectibles;
	t_vwall		*vwall;
}	t_game;

#endif