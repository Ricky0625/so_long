/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:06:29 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/19 19:25:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Basically a strchr but instead of searching for a character in a string,
 * search for a tile in a tilemap
**/
t_tile	*tilechr(t_tile *tile, t_tiletype type)
{
	while (tile->type != 0)
	{
		if (tile->type == type)
			return (tile);
		tile++;
	}
	return (0);
}
