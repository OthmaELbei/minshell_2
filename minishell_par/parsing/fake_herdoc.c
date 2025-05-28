/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:50:44 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/27 22:57:09 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_child_process(char *delimiter)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if ((!line) || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
	}
	exit(0);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (write(1, "\n", 1), -13);
	return (0);
}

int	open_herdoc_error(char *delimter, int *n, t_listenv *head)
{
	char	**exp;
	char	*new_delimter;
	int		result;
	pid_t	pid;

	pid = 0;
	result = 0;
	exp = ft_expand_herdoc(delimter, n, head);
	new_delimter = exp[0];
	pid = fork();
	if (pid == 0)
		handle_child_process(new_delimter);
	else
		result = handle_parent_process(pid);
	free(exp);
	free(new_delimter);
	return (result);
}

int	ft_open_herdoc_until_error(t_token *current, t_listenv *head)
{
	int	n;

	n = 10;
	while (current)
	{
		if (current->error == -1)
			return (-1);
		if ((current->type == HERDOC
				&& current->next && current->next->type == F_HERDOC))
		{
			if (current->error == -1 || current->next->error == -1)
				break ;
			if (open_herdoc_error(current->next->value[0], &n, head) == -13)
				return (-13);
		}
		current = current->next;
	}
	return (0);
}
