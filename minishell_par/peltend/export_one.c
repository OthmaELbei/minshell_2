/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:18:45 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 20:32:52 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_listenv	*tcchk_untel_egall(char *data, t_listenv *head)
{
	while (head)
	{
		if (!ft_strcmp(data, head->constvrble))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

int	tcchk_untel_egll(char *data, t_listenv *head)
{
	while (head)
	{
		if (ft_strcmp(data, head->constvrble) == 0)
		{
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	ft_tchck_argmo_exat(char *data)
{
	int	i;

	i = 0;
	if (!data || !(ft_isalpha(data[0]) || data[0] == '_'))
		return (0);
	while (data[i] && data[i] != '=' && !(data[i] == '+' && data[i + 1] == '='))
	{
		if (data[i] == ' ')
		{
			return (0);
		}
		if (!(ft_isalnum(data[i]) || data[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	tchek_only_key(char *data, t_expcall *call, t_listenv **head)
{
	t_listenv	*found;
	char		*tmp;

	found = NULL;
	tmp = NULL;
	if (tcchk_untel_egll(call->splt_egal, *head) == 1)
	{
		found = tcchk_untel_egall(call->splt_egal, *head);
		free(found->constvrble);
		tmp = ft_strjoin(call->splt_egal, "=");
		if (tmp)
			found->constvrble = tmp;
	}
	else if (tcchk_untel_egll(call->splt_plus[0], *head)
		== 1 && ft_strchr(data, '+'))
	{
		found = tcchk_untel_egall(call->splt_plus[0], *head);
		free(found->constvrble);
		tmp = ft_strjoin(call->splt_plus[0], "=");
		if (tmp)
			found->constvrble = tmp;
	}
}

void	free_copy_listenv(t_listenv *head)
{
	t_listenv	*head_new;

	while (head)
	{
		head_new = head;
		head = head->next;
		free(head_new->constvrble);
		free(head_new->pat);
		free(head_new);
	}
}
