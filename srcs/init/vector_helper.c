/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:43:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/05 14:43:53 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initialize the vector
 */
void	vector_init(t_vector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

/**
 * @brief Set the vector based on the given input
 */
void	set_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

/**
 * @brief Check if two vector has the same value
 */
int	is_same_vector(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y);
}
