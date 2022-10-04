/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:30:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/04 12:04:57 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	player_init(t_game *game, t_player *player)
{
	player->collected = 0;
	player->moves = 0;
	anim_init(&player->anim, 12, game->img_db.player_idle);
}

void	add_player(t_game *game, int x, int y)
{
	t_player	*ply;

	ply = &game->player;
	player_init(game, ply);
	ply->loc.x = x;
	ply->loc.y = y;
}
