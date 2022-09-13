/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:01:34 by wricky-t          #+#    #+#             */
/*   Updated: 2022/09/13 19:03:18 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * Initialize vector
**/
void	vector_init(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

/**
 * Set vector with given parameter
**/
void	set_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}
