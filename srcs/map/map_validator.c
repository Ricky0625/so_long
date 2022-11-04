/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:05:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:12:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Check if the file extension is accepted or not
 *
 * ext		: The file extension of the map (input)
 * cmp_len	: Length that will be used for strncmp
 *
 * 1. Use ft_strrchr to locate the last occurrence of '.'.
 * 2. Get the len of valid file extension ".ber", which will always be 4
 * 3. If the file extension is NULL, it means not file extension found
 * 4. If we want to use ft_strncmp, we have to use the length of longer
 * 	  string for our last parameter. But instead of doing that, check if
 * 	  the input file name's file extension length is greater than 4. If
 *    yes, that definitely is not the valid file extension.
 *    If input file length is less or equal, use strncmp. If not 0,
 * 	  meaning it's not a valid file extension.
 * 5. When it's not a valid file extension, output error msg and exit.
 **/
static void	check_map_name(t_game *game)
{
	char	*file;
	char	*ext;
	size_t	cmp_len;

	file = game->map_data.file;
	ext = ft_strrchr(file, '.');
	cmp_len = ft_strlen(FILE_EXT);
	if (ext == NULL || ft_strlen(ext) > cmp_len
		|| ft_strncmp(ext, FILE_EXT, cmp_len) != 0)
		exit_game(game, "File extension not supported!", FAILURE);
}

/**
 * @brief Get raw map (Unprocessed map, not checked)
 *
 * Strjoin all the line all together into a string
 * 1. Use gnl to read all the lines from the file
 * 2. If the str is null, meaning, it reaches the end. The process is done.
 * 	  If the str is not null and raw is null, meaning, it's reading the
 * 	  first line. So just assign the first line to raw and continue to
 *    next iteration.
 * 3. Strjoin raw with the output of gnl.
 **/
static void	get_raw_map(t_game *game, int fd)
{
	char	*str;
	char	*raw;
	char	*temp;

	raw = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		else if (raw == NULL)
		{
			raw = str;
			continue ;
		}
		temp = raw;
		raw = ft_strjoin(raw, str);
		free(temp);
		free(str);
	}
	game->map_data.raw = raw;
}

/**
 * @brief Get the size of the map
 * This does not check if the map is valid or not.
 *
 * 1. Get the width of the map
 * 	  Count the first line until it encounters '\n' OR '\0'
 *    Basically using first line as a ruler.
 * 2. Reset pointer to the base address of raw
 * 3. Get the height of the map
 * 	  Count the number of '\n' in a map. Start counting from
 * 	  1 which means we already consider the last line as one
 * 	  line (it does not end with '\n')
 * 4. Set width and height to the map_data
 **/
static void	get_map_size(t_game *game, char *raw)
{
	int	width;
	int	height;

	width = 0;
	height = 1;
	if (raw == NULL)
	{
		free(game->map_data.raw);
		exit_game(game, "Empty map!", FAILURE);
	}
	while (*raw != '\n' && *raw != '\0')
	{
		width++;
		raw++;
	}
	raw -= width;
	while (*raw != '\0')
	{
		if (*raw == '\n')
			height++;
		raw++;
	}
	game->map_data.size.x = width;
	game->map_data.size.y = height;
}

/**
 * @brief Validate the map
 *
 * 1. Start by checking if the file extension is accepted
 * 2. Get the raw map in a string format
 * 3. Calculate the width and height
 * 4. Split raw map into 2D array
 * 5. Set the map to map_data
 * 6. Check map format
 * 7. Add aesthetic (makes the game looks more like a top down game)
 **/
void	map_validator(t_game *game, char *file)
{
	int		fd;
	char	**map;

	game->map_data.file = file;
	check_map_name(game);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_game(game, "File does not exist!", FAILURE);
	get_raw_map(game, fd);
	get_map_size(game, game->map_data.raw);
	map = ft_split(game->map_data.raw, '\n');
	game->map_data.map = map;
	check_map_format(game);
	add_aesthetic(game);
	free(map);
	close(fd);
}
