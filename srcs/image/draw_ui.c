/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:36:27 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/04 20:42:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Place the image of the numbers onto the screen
 * 
 * The numbers are stored in a array. Like 0 is at index 0, 1 at index 1, etc.
 * So, just itoa the player's moves count and iterate through the str.
 * For each character, minus it with '0' and we can get the index number.
 * Use that to access which image to display. After that just put to the
 * screen
 */
void	draw_ui(t_game *game)
{
	char		*str;
	t_image		*num;
	int			loc_y;

	str = ft_itoa(game->player.moves);
	loc_y = 32;
	while (*str != '\0')
	{
		num = game->img_db.numbers[(*str - '0')];
		mlx_put_image_to_window(game->ref, game->win, num->ref, loc_y, 32);
		loc_y += 64;
		str++;
	}
}
