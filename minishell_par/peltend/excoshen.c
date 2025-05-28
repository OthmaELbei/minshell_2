/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/28 12:08:50 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (ft_tchee_redercter(current, head) == 1)
			return (1);
	}
	return (0);
}

int	run_cmd(t_data *current, int prev_fd, int *pipe_fd, t_listenv **head)
{
	int		status;
	char	**env_ar;
	char	*cmd_path;
	pid_t	pid;

	// if (!*head || !head)
	// 	return (0);
	// printf("knkhkjhkj\n");
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
	return (ft_tchck_status(status));
}

int	complet_execoshen(t_data *current,
		int prev_fd, int *pipe_fd, t_listenv **head)
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
			exit(run_cmd(current, prev_fd, pipe_fd, head));
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

int	ft_execoshen(t_data *data, t_listenv **head)
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
		return (run_cmd(current, prev_fd, pipe_fd, head));
	status = complet_execoshen(current, prev_fd, pipe_fd, head);
	return (ft_tchck_status(status));
}
