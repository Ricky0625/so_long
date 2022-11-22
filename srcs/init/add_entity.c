/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:16:18 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/22 14:14:28 by wricky-t         ###   ########.fr       */
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
	anim_init(&ply->anim, PLAYER_AD, game->img_db.player_idle_r);
}

/**
 * @brief Initialize and add ghost to game
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the ghost
 */
void	add_ghost(t_game *game, t_vector loc)
{
	t_ghost		*ghost;
	t_entity	entity_data;

	ghost = &game->ghost;
	entity_data = game->entity;
	if (entity_data.skely > 0)
		ghost->appear_counter = entity_data.coll * APPEAR_MULTIPLIER;
	else
		ghost->appear_counter = 0;
	ghost->activate = 0;
	ghost->loc = loc;
	anim_init(&ghost->anim, GHOST_AD, game->img_db.ghost_idle);
	anim_init(&ghost->effect, GHOST_BOO_AD, game->img_db.ghost_boo);
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
	skely->loc = loc;
	skely->dir = UNSET;
	skely->current_tick = 0;
	anim_init(&skely->anim, SKELY_AD, game->img_db.skeleton_idle_l);
	ft_lstadd_back(skeletons, ft_lstnew(skely));
}

/**
 * @brief Add the entity based on the entity type
 * 
 * This will be used while iterating through the map.
 */
void	add_entity(t_game *game, t_enty_type type, t_vector loc)
{
	if (type == PLAYER)
		add_player(game, loc);
	else if (type == GHOST)
		add_ghost(game, loc);
	else if (type == SKELETON)
		add_skeleton(game, loc);
	else if (type == COLLECTIBLE)
		add_collectible(game, loc);
	else if (type == VWALL)
		add_vwall(game, loc);
	else if (type == EXIT)
		add_exit(game, loc);
}

/**
 * @brief Add entity
 * 
 * Iterate through the map and add the info of the entity to game struct
 */
void	update_entity(t_game *game)
{
	t_vector	loc;
	char		entity;
	char		**map;

	loc.x = -1;
	map = game->map_data.map;
	while (map[++loc.x] != NULL)
	{
		loc.y = -1;
		while (map[loc.x][++loc.y] != '\0')
		{
			entity = map[loc.x][loc.y];
			add_entity(game, entity, loc);
		}
	}
}
