/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_mechanism.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:39:23 by wricky-t          #+#    #+#             */
/*   Updated: 2022/10/31 20:55:25 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	is_key(t_game *game, t_vector loc)
{
	t_list	*collectibles;
	t_coll	*coll;

	collectibles = game->collectibles;
	while (collectibles != NULL)
	{
		coll = collectibles->content;
		if (is_same_vector(coll->loc, loc) == 1)
			return (1);
		collectibles = collectibles->next;
	}
	return (0);
}

// instead of just set collected to 1, free the node
static void	collect_key(t_game *game, t_vector loc)
{
	t_list	*collectibles;
	t_coll	*coll;

	collectibles = game->collectibles;
	while (collectibles != NULL)
	{
		coll = collectibles->content;
		if (is_same_vector(coll->loc, loc) == 1)
			break ;
		collectibles = collectibles->next;
	}
	if (collectibles == NULL)
		return ;
	ft_lstdelnode(&game->collectibles, collectibles);
	game->player.collected++;
}

int	get_killed(t_game *game, t_vector dest)
{
	t_list		*skeletons;
	t_skeleton	*skely;

	skeletons = game->skeletons;
	while (skeletons != NULL)
	{
		skely = skeletons->content;
		if (is_same_vector(skely->loc, dest) == 1 && skely->killed == 0)
			return (1);
		skeletons = skeletons->next;
	}
	return (0);
}

/**
 * @brief Check if an entity will experience collision.
 */
/**
 * General
 * 1. Wall, vwall will cause collision
 * 
 * PLAYER
 * 1. When step on ghost's tile, decrement appear counter
 * 2. When step on a key, collect it
 * 3. When step on exit && player collected all keys, exit.
 * 4. If step on a skeleton, die.
 * 
 * SKELETON
 * 1. Cannot go pass ghost
 * 2. Cannot go pass skeleton
 * 3. Cannot go pass a key
 * 4. Can go pass a exit
 * 5. Cannot go pass player, otherwise player die
 */
int	detect_collision(t_game *game, t_vector dest, t_enty_type type)
{
	char	enty;

	enty = game->map_data.map[dest.x][dest.y];
	if (enty == WALL || enty == VWALL)
		return (1);
	if (type == PLAYER)
	{
		collect_key(game, dest);
		if (enty == GHOST && game->ghost.appear_counter > 0)
			game->ghost.appear_counter--;
		if (enty == EXIT && game->player.collected == game->entity.coll)
			exit(0);
		if (get_killed(game, dest) == 1)
			exit(0);
	}
	if (type == SKELETON)
	{
		if (enty == GHOST || is_key(game, dest) == 1
			|| get_killed(game, dest) == 1 || enty == EXIT)
			return (1);
		else if (is_same_vector(dest, game->player.loc))
			return (-1);
	}
	return (0);
}
