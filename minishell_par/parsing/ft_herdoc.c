/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/20 13:23:17 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	helper_function(char *delimter, char *line,
						int helper_fd, t_listenv *head)
{
	char	**exp;
	char	*new_line;
	int		n;

	new_line = NULL;
	exp = NULL;
	n = 1377;
	if (check_delimter(delimter) == 0)
	{
		exp = ft_expand_herdoc(line, &n, head);
		new_line = exp[0];
		write(helper_fd, new_line, ft_strlen(new_line));
		write(helper_fd, "\n", 1);
	}
	else
	{
		write(helper_fd, line, ft_strlen(line));
		write(helper_fd, "\n", 1);
	}
	(free(line), free(new_line), free(exp));
}

int	open_herdoc(char *delimter, char *random_name, int *n, t_listenv *head)
{
	int		fd[2];
	char	*line;
	char	**exp;
	char	*new_delimter;

	exp = ft_expand_herdoc(delimter, n, head);
	new_delimter = exp[0];
	random_name = generate_name();
	fd[0] = open(random_name, O_RDWR | O_CREAT, 0777);
	fd[1] = open (random_name, O_RDONLY | O_CREAT, 0777);
	if (unlink(random_name) || (fd[0] < 0) || (fd[1] < 0))
		return (perror("faile"), close(fd[0]), close(fd[1]), -1);
	while (1)
	{
		line = readline("> ");
		if ((!line) || ft_strcmp(line, new_delimter) == 0)
		{
			free(line);
			break ;
		}
		helper_function(delimter, line, fd[0], head);
	}
	return (free(random_name), free(exp), free(new_delimter), close(fd[0]),
		fd[1]); // should close the return file descriptor
}

void	ft_herdoc(t_token **tokens, t_listenv *head)
{
	t_token	*current;
	int		fd_;
	int		n;
	char	*random_name;

	random_name = NULL;
	n = 10;
	fd_ = -1;
	current = *tokens;
	while (current)
	{
		if (current->type == HERDOC
			&& current->next && current->next->type == F_HERDOC)
		{
			fd_ = open_herdoc(current->next->value[0], random_name, &n, head);
			if (fd_ != -1)
				current->next->fd = fd_;
			// else if (fd_ == -1)
				// exit(1);
		}
		current = current->next;
	}
}
