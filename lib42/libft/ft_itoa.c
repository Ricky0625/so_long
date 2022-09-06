/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:17:00 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 10:38:28 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// get number of digit
static int	get_no_digit(int n)
{
	int	num;
	int	no_digit;

	num = n;
	no_digit = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		num *= -1;
	while (num)
	{
		num /= 10;
		no_digit++;
	}
	return (no_digit);
}

// malloc str
// if n is negative, malloc size will be no_digit + 2 (1 for '-', 1 for \0)
// if n is positive, malloc size will be no_digit + 1 (1 for \0)
static char	*malloc_str(int n, int no_digit)
{
	char	*str;

	if (n < 0)
		str = malloc(sizeof(char) * (no_digit + 2));
	else
		str = malloc(sizeof(char) * (no_digit + 1));
	return (str);
}

// times how many, use to calculate the place value
static int	times(int no_digit)
{
	int	times;

	times = 1;
	while (--no_digit)
		times *= 10;
	return (times);
}

// the main logic: convert int to char
// at first, it checks whether n is negative or not
// if yes, we insert the sign '-' first then abs(n)
// if the n is INT_MIN, we insert '2' to the str, and then set n as 147483648
// no_digit-- because we ady handle one digit '2'

// the idea is to extract the digit of the n from the front to back
// by using n / place_value we can get the digit in the front
// by using n %= place_value we can get the remaining digit

// example: -789 has 3 digit; 789 has 3 digit
// run the loop until all the digit has been processed, so need no_digit--
// loop will stop when no_digit = 0, meaning all digit has been processed

// since it's a string so we have to null-terminated it at last
static void	insert_char(char *str, int n, int no_digit)
{
	int	index;
	int	place_value;

	index = 0;
	if (n < 0)
	{
		str[index++] = '-';
		if (n == -2147483648)
		{
			str[index++] = '2';
			n = 147483648;
			no_digit--;
		}
		else
			n *= -1;
	}
	while (no_digit)
	{
		place_value = times(no_digit);
		str[index++] = (n / place_value) + '0';
		n %= place_value;
		no_digit--;
	}
	str[index] = '\0';
}

char	*ft_itoa(int n)
{
	int		no_digit;
	char	*str;

	no_digit = get_no_digit(n);
	str = malloc_str(n, no_digit);
	if (str == NULL)
		return (NULL);
	insert_char(str, n, no_digit);
	return (str);
}
