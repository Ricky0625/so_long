/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanism.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:03:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/01 15:43:36 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ghost_boo(t_game *game)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	skeletons = game->skeletons;
	if (game->ghost.appear_counter > 0 || game->entity.skely == 0)
		return ;
	game->ghost.activate = 1;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		skely->anim.frames = game->img_db.skeleton_scared;
		skeletons = skeletons->next;
	}
}

void	move_player(t_game *game, int key)
{
	t_vector	dest;

	set_vector(&dest, game->player.loc.x, game->player.loc.y);
	if (key == KEY_W)
		dest.x--;
	else if (key == KEY_A)
	{
		game->player.anim.frames = game->img_db.player_idle_l;
		dest.y--;
	}
	else if (key == KEY_S)
		dest.x++;
	else if (key == KEY_D)
	{
		game->player.anim.frames = game->img_db.player_idle_r;
		dest.y++;
	}
	else if (key == KEY_SP && game->ghost.activate == 0)
		ghost_boo(game);
	if (detect_collision(game, dest, PLAYER) == 0)
	{
		set_vector(&game->player.loc, dest.x, dest.y);
		game->player.moves++;
	}
}
