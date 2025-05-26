/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/26 10:19:37 by oelbied          ###   ########.fr       */
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

int	tf_tchee_redercter(t_data *data, t_listenv **head)
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
			ft_tchek_herdok(redir);
			redir = redir->next;
			continue ;
		}
		if (fd == -1)
			return (perror(data->file->name), 1);
		if (redir->type == FWRITE_OUT || redir->type == F_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (redir->type == FREAD_IN)
			dup2(fd, STDIN_FILENO);
		ft_closse(redir, fd);
		redir = redir->next;
	}
	return (0);
}

void	ft_tchk_not_peltend(t_data *data, char **env_ar, char *cmd_path,int	*status)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (execve(cmd_path, data->args, env_ar) == -1)
	{

		*status = 127;
		if(data->args[0] != NULL)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(data->args[0], 2);
			ft_putstr_fd(": command not found++\n", 2);
		}
		exit(*status);
	}
}

int	status_res(int status)
{
	if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status) + 128);
	}
	return (WEXITSTATUS(status));
}

int	run_cmd_frist(t_data *current,
	int prev_fd, int *pipe_fd, t_listenv **head)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (current->file)
	{
		if (tf_tchee_redercter(current, head) == 1)
			return (1);
	}
	return (0);
}

int run_cmd(t_data *current, int prev_fd, int *pipe_fd, t_listenv **head)
{
	int		status;
	char	**env_ar;
	char	*cmd_path;
	pid_t	pid;

	if (!*head || !head)
		return (0);
	run_cmd_frist(current, prev_fd, pipe_fd, head);
	if (is_builtin(current, head) == 1)
		return (ft_tchc_data(current, head));
	pid = fork();
	if (pid == 0)
	{
		env_ar = ft_ar_env(*head);
		if (current->args == NULL)
			exit(0);
		cmd_path = get_command_path(current->args[0], env_ar, &status);
		if (cmd_path == NULL)
			exit(status);
		ft_tchk_not_peltend(current, env_ar, cmd_path, &status);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (status_res(status));
}

int	complet_execoshen(t_data *current,
		int prev_fd, int *pipe_fd, t_listenv *head)
{
	pid_t	pid;
	int		status;

	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
			ft_erorr("pipe");
		pid = fork();
		if (pid == -1)
			ft_erorr("fork");
		if (pid == 0)
			exit(run_cmd(current, prev_fd, pipe_fd, &head));
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		current = current->next;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (status);
}

int	ft_execoshen(t_data *data, t_listenv *head)
{
	t_data		*current;
	int			pipe_fd[2];
	int			prev_fd;
	int			status;

	prev_fd = -1;
	current = data;
	if (!data || !head)
		return (0);
	if (current->next == NULL)
		return (run_cmd(current, prev_fd, pipe_fd, &head));
	status = complet_execoshen(current, prev_fd, pipe_fd, head);
	return (status_res(status));
}
