/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen_tows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:39:07 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/28 12:02:21 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	all_redercter(t_data *data, t_redir *redir, int *fd)
{
	if (data->file->_ambigous != ambigous)
	{
		if (redir->type == FWRITE_OUT)
			*fd = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == FREAD_IN)
			*fd = open(redir->name, O_RDONLY);
		else if (redir->type == F_APPEND)
			*fd = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		return (1);
	}
	return (0);
}

int	ft_tchee_redercter(t_data *data, t_listenv **head)
{
	t_redir	*redir;
	int		fd;

	(void)head;
	fd = -1;
	redir = data->file;
	while (redir)
	{
		all_redercter(data, redir, &fd);
		if (redir->type == F_HERDOC)
		{
			ft_tchek_herdok(&redir);
			fd = 5;
			// redir = redir->next;
			// continue ;
		}
		if (fd == -1)
			return (perror(redir->name), 1);
		if (redir->type == FWRITE_OUT || redir->type == F_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (redir->type == FREAD_IN)
			dup2(fd, STDIN_FILENO);
		ft_closse(redir, fd);
		redir = redir->next;
	}
	return (0);
}

void	ft_tchk_not_peltend(t_data *data,
	char **env_ar, char *cmd_path, int	*status)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (execve(cmd_path, data->args, env_ar) == -1)
	{
		*status = 127;
		if (data->args[0] != NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(data->args[0]);
		}
		exit(*status);
	}
}

int	ft_tchck_status(int status)
{
	if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status) + 128);
	}
	return (WEXITSTATUS(status));
}
