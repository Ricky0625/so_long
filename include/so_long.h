/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:32:55 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/07 14:52:28 by wricky-t         ###   ########.fr       */
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

typedef struct s_entity {
	int	plyr;
	int	coll;
	int	exit;
	int	enem;
}	t_entity;

/**
 * Game - To store all the info I need
 * ref		: mlx instance pointer
 * window	: pointer to window struct
**/
typedef struct s_game {
	void		*ref;
	t_window	*window;
	t_map		map_data;
	t_entity	enty;
}	t_game;

// Game init
t_game	*game_init(int ac, char **av);

// Map Validator
void	map_validator(t_game *game, char *file);
void	check_map_format(t_game *game);

// Map utils
void	is_rectangular(t_game *game);
void	get_entity(t_game *game, char ch);
void	find_entity(t_vector *loc, char **map, char enty);
char	**copy_map(t_game *game, char **map);

// Pathfinder
void	fill_map(t_vector *start, char **map);

// free
void	free_map(char **map);
void	free_game(t_game *game);

#endif