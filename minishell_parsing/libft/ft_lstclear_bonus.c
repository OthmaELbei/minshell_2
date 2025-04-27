/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:25:18 by oelbied           #+#    #+#             */
/*   Updated: 2024/11/12 16:51:24 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	if (lst == NULL || del == NULL)
	{
		return ;
	}
	temp = *lst;
	while (temp != NULL)
	{
		next = temp -> next;
		del(temp -> content);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}
