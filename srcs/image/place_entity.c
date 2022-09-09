/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_entity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:53:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/09 13:10:29 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

char	*get_entity_sprite(t_game *game, int x, int y)
{
	char		**map;
	char		enty;
	t_vector	size;

	map = game->map_data.map;
	enty = map[x][y];
	size.x = game->map_data.size.x;
	size.y = game->map_data.size.y;
	if (x == 0 || y == 0 || x == size.y - 1 || y == size.x - 1)
		return (NULL);
	if (enty == 'P')
		return (P);
	if (enty == 'M')
		return (M);
	if (enty == 'G')
		return (G);
	if (enty == '0')
		return (F);
	if (enty == 'C')
		return (C);
	if (enty == '1')
		return (B);
	if (enty == 'E')
		return (EC);
	return (NULL);
}

void	place_entity_sprite(t_game *game, int x, int y)
{
	char	*enty;

	enty = get_entity_sprite(game, x, y);
	if (enty == NULL)
		return ;
	place_sprite(game, enty, x, y);
}
