/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:35:19 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 18:06:36 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	free_head(t_list **lst)
{
	t_list	*curr;

	curr = *lst;
	*lst = (*lst)->next;
	free(curr->content);
	free(curr);
}

/**
 * Delete the target node from the lst
 * 
 * If the lst is null, return.
 * If the target is the head, free head.
 * If the target is not head,
 */
void	ft_lstdelnode(t_list **lst, t_list *target)
{
	t_list	*curr;
	t_list	*prev;

	if (*lst == NULL)
		return ;
	if (*lst == target)
		free_head(lst);
	else
	{
		prev = *lst;
		curr = (*lst)->next;
		while (curr != NULL)
		{
			if (curr == target)
			{
				prev->next = curr->next;
				free(target->content);
				free(target);
				return ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}
