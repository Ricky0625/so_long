/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:37:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/17 12:42:35 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initialize and add vertical wall to its list
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the vertical wall
 * 
 * @details
 * Allocate memory for one vertical wall and add it to the
 * vertical wall list
 */
void	add_vwall(t_game *game, t_vector loc)
{
	t_list	**vwalls;
	t_vwall	*vwall;

	vwalls = &game->vwalls;
	vwall = malloc(sizeof(t_vwall));
	anim_init(&vwall->anim, 10, game->img_db.vwall_idle);
	vwall->loc = loc;
	ft_lstadd_back(vwalls, ft_lstnew(vwall));
}

/**
 * @brief Initialize and add player to its list
 * 
 * @param game 	: the game struct
 * @param loc	: the location of the collectible
 * 
 * @details
 * Allocate memory for one collectible and add it to the
 * collectible list
 */
void	add_collectible(t_game *game, t_vector loc)
{
	t_list	**colls;
	t_coll	*coll;

	colls = &game->collectibles;
	coll = malloc(sizeof(t_coll));
	coll->collected = 0;
	anim_init(&coll->anim, 10, game->img_db.key_idle);
	coll->loc = loc;
	ft_lstadd_back(colls, ft_lstnew(coll));
}

void	add_exit(t_game *game, t_vector loc)
{
	t_exit	*exit;

	exit = &game->exit;
	exit->clear = 0;
	exit->loc = loc;
	anim_init(&exit->anim, 10, game->img_db.exit);
}
