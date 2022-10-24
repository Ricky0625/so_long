/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:16:18 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/22 17:10:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initialize and add player to game
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the player
 */
void	add_player(t_game *game, t_vector loc)
{
	t_player	*ply;

	ply = &game->player;
	ply->collected = 0;
	ply->moves = 0;
	ply->loc = loc;
	anim_init(&ply->anim, 18, game->img_db.player_idle);
}

/**
 * @brief Initialize and add ghost to game
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the ghost
 */
void	add_ghost(t_game *game, t_vector loc)
{
	t_ghost	*ghost;

	ghost = &game->ghost;
	ghost->appear_counter = 0;
	ghost->loc = loc;
	anim_init(&ghost->anim, 10, game->img_db.ghost_idle);
}

/**
 * @brief Initialize and add skeleton to its list
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the skeleton
 * 
 * @details
 * Allocate memory for one skeleton and add it to the
 * skeleton list
 */
void	add_skeleton(t_game *game, t_vector loc)
{
	t_list		**skeletons;
	t_skeleton	*skely;

	skeletons = &game->skeletons;
	skely = malloc(sizeof(t_skeleton));
	skely->collide = 0;
	anim_init(&skely->anim, 18, game->img_db.skeleton_idle);
	skely->loc = loc;
	ft_lstadd_back(skeletons, ft_lstnew(skely));
}
