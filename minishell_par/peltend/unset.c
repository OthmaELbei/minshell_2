/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:16 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/28 11:15:10 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_del(void *ptr)
{
	free(ptr);
}

t_listenv	*inte_unset(t_listenv *curr,
	t_listenv *prev, t_listenv **head, t_unset *pactge)
{
	t_listenv	*tmp;
	tmp = curr->next;
	if (prev != NULL)
		prev->next = tmp;
	else
	{
		printf("if hear\n");
		// printf("%s\n",tmp->constvrble);
		// printf("%s\n",(*head)->constvrble);
		(*head) = tmp;
	}
	ft_lstdelone(curr, my_del);
	pactge->flags = 1;
	return (tmp);
}

int	swap_unset(t_listenv *curr,
	t_listenv *prev, t_listenv **head, t_unset *pactge)
{
	char	*cope;

	while (curr)
	{
		cope = ft_strdup_unset(curr->constvrble);
		if(!cope)
			return(0);
		if (!ft_strcmp(pactge->data, cope))
		{
			curr = inte_unset(curr, prev, head, pactge);
		}
		else
		{
			prev = curr;
			curr = curr->next;
			// free(cope);
		}
		// if (cope)
			free(cope);
	}
	return (pactge->flags);
}

int	ft_unset(t_data *data, t_listenv **head)
{
	t_listenv	*curr;
	t_listenv	*prev;
	int			flags;
	int			i;

	flags = 0;
	i = 1;
	while (data->args[i] != NULL)
	{
		if (ft_tchk_value(data->args[i]))
		{
			printf("unset: `%s': not a valid identifier\n", data->args[i]);
			i++;
			continue ;
		}
		curr = *head;
		prev = NULL;
		flags = swap_unset(curr, prev, head, &(t_unset){flags, data->args[i]});
		i++;
		flags = 0;
	}
				printf("hola amgos\n");
	return (0);
}
