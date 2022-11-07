/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:04:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/11/07 13:38:23 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	ft_lstdelall(t_list	*head)
{
	t_list	*temp;

	temp = head;
	while (temp != NULL)
	{
		temp = temp->next;
		free(head->content);
		free(head);
		head = temp;
	}
}
