/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:22:34 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/09 16:03:56 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsize(t_listenv *lst)
{
	int		cont;
	t_listenv	*pt_nod;

	cont = 0;
	if (lst == NULL)
		return (0);
	pt_nod = lst;
	while (pt_nod != NULL)
	{
		cont++;
		pt_nod = pt_nod -> next;
	}
	return (cont);
}
int	ft_lstsize_data(t_data *lst)
{
	int		cont;
	t_data	*pt_nod;

	cont = 0;
	if (lst == NULL)
		return (0);
	pt_nod = lst;
	while (pt_nod != NULL)
	{
		cont++;
		pt_nod = pt_nod -> next;
	}
	return (cont);
}
