/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:44 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/20 13:09:32 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_herdoc_error(char *delimter, int *n, t_listenv *head)
{
	char	*line;
	char	**exp;
	char	*new_delimter;

	exp = ft_expand_herdoc(delimter, n, head);
	new_delimter = exp[0];
	while (1)
	{
		line = readline("> ");
		if ((!line) || ft_strcmp(line, new_delimter) == 0)
		{
			free(line);
			break ;
		}
	}
	return (free(exp), free(new_delimter));
}

void	ft_open_herdoc_until_error(t_token *current, t_listenv *head)
{
	int	n;

	n = 10;
	while (current)
	{
		if (current->error == -1)
			return ;
		if ((current->type == HERDOC
				&& current->next && current->next->type == F_HERDOC))
		{
			if (current->error == -1 || current->next->error == -1)
				break ;
			open_herdoc_error(current->next->value[0], &n, head);
		}
		current = current->next;
	}
}
