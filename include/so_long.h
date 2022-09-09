/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:32:55 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/09 13:39:58 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "../lib42/lib42.h"
# include <stdio.h>
# include <stdlib.h>

// Text styling
# define RED "\033[0;31m"
# define YL "\033[0;33m"
# define GN "\033[0;32m"
# define DEF "\033[0m"

// Macros
# define FILE_EXT ".ber"
# define SPT_SIZE 64
# define GNAME "so_long: "

// Sprite
# define P "assets/xpm/player.xpm"
# define M "assets/xpm/enemy.xpm"
# define G "assets/xpm/ghost.xpm"
# define F "assets/xpm/floor.xpm"
# define C "assets/xpm/key.xpm"
# define B "assets/xpm/block.xpm"
# define EO "assets/xpm/exit.xpm"
# define EC "assets/xpm/exit_close.xpm"
# define WU "assets/xpm/wall_u.xpm"
# define WD "assets/xpm/wall_d.xpm"
# define WL "assets/xpm/wall_l.xpm"
# define WR "assets/xpm/wall_r.xpm"
# define WV "assets/xpm/wall_v.xpm"
# define WUL "assets/xpm/wall_ul.xpm"
# define WUR "assets/xpm/wall_ur.xpm"
# define WDL "assets/xpm/wall_dl.xpm"
# define WDR "assets/xpm/wall_dr.xpm"

/**
 * Vector
 * x	: width / x-axis position
 * y	: height / y-axis position
**/
typedef struct s_vector {
	int	x;
	int	y;
}	t_vector;

/**
 * Window
 * ref	: Window instance pointer
 * size	: width & height of window
**/
typedef struct s_window {
	void		*ref;
	t_vector	size;
}	t_window;

/**
 * Metadata of map
 * 
 * map	: the map
 * size	: width & height of the map
**/
typedef struct s_map {
	char		*raw;
	char		**map;
	char		*file;
	t_vector	size;
}	t_map;

/**
 * Metadata of the entity
 * 
 * Store the number of:
 * 1. player
 * 2. collectibles
 * 3. exit
 * 4. enemy
**/
typedef struct s_entity {
	int	plyr;
	int	coll;
	int	exit;
	int	enem;
	int	ghost;
}	t_entity;

typedef struct s_image {
	void		*ref;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}	t_image;

/**
 * Game - To store all the info I need
 * ref		: mlx instance pointer
 * window	: pointer to window struct
**/
typedef struct s_game {
	void		*ref;
	t_window	window;
	t_map		map_data;
	t_entity	enty;
}	t_game;

// Init
t_game	*game_init(int ac, char **av);
void	window_init(t_game *game);
void	init_vector(t_vector *vector);
void	image_init(t_image *image);

// Map Validator
void	map_validator(t_game *game, char *file);
void	check_map_format(t_game *game);

// Map utils
void	is_rectangular(t_game *game);
void	get_entity(t_game *game, char ch);
void	find_entity(t_vector *loc, char **map, char enty);
char	**copy_map(t_game *game, char **map);
char	**add_aesthetic(t_game *game);

// Pathfinder
void	fill_map(t_vector *start, char **map);
void	show_path(char **map);

// image
void	place_sprite(t_game *game, char *sprite, int x, int y);
void	mapiteri(t_game *game, void (*f)(t_game *, int, int));
void	place_wall_sprite(t_game *game, int x, int y);
void	place_entity_sprite(t_game *game, int x, int y);
void    place_map(t_game *game);

// free
void	free_map(char **map);
void	free_game(t_game *game);

#endif