/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:40:19 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:21:40 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// applies the function f on each character of s
// the 1st argument of f is the index
// the 2nd argument of f is the character

// different than strmapi, this function does not use malloc

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;
	size_t			len;

	if (!s)
		return ;
	len = ft_strlen(s);
	index = 0;
	while (*(s + index))
	{
		f(index, (s + index));
		index++;
	}
	*(s + index) = '\0';
}
