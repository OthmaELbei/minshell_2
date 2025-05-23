/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoert_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:41:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 10:52:01 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_listenv	*find_variable(t_listenv *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->constvrble, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	find_varble(t_listenv *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->constvrble, name))
			return (1);
		head = head->next;
	}
	return (0);
}

void	ft_free_ex(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_listenv	*copy_listenv(t_listenv *head)
{
	t_listenv	*new_head;
	t_listenv	*last;
	t_listenv	*new_node;

	new_head = NULL;
	last = NULL;
	if (head == NULL)
		return (NULL);
	while (head)
	{
		new_node = malloc(sizeof(t_listenv));
		if (!new_node)
			return (NULL);
		new_node->constvrble = ft_strdup(head->constvrble);
		new_node->pat = ft_strdup(head->pat);
		new_node->next = NULL;
		if (!new_head)
			new_head = new_node;
		else
			last->next = new_node;
		last = new_node;
		head = head->next;
	}
	return (new_head);
}

void	cleanup_memory(char *splt_egal, char **splt_plus, char *segal)
{
	if (splt_egal)
		free(splt_egal);
	if (segal)
		free(segal);
	if (splt_plus)
		ft_free_ex(splt_plus);
}
