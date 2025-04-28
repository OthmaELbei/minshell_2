/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:13:30 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/20 08:39:41 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstdelone(t_listenv *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
	{
		return ;
	}
	del(lst->constvrble);
	del(lst->pat);
	
	free(lst);
}
