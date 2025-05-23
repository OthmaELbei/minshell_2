/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/23 14:17:50 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	thcke_fd(int fd)
{
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	ft_closse(t_redir *redir, int fd)
{
	if (redir->type == FWRITE_OUT
		|| redir->type == FREAD_IN || redir->type == F_APPEND)
	{
		thcke_fd(fd);
		close(fd);
	}
}

void	ft_tchek_herdok(t_redir *redir)
{
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	redir = redir->next;
}

void	ft_erorr(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int tf_tchee_redercter(t_data *data, t_listenv **head)
{
	t_redir *redir;
(void)head;
	int fd = -1;
	redir = data->file;
	while (redir)
	{
		if (redir->type == FWRITE_OUT)
			fd = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == FREAD_IN)
			fd = open(redir->name, O_RDONLY);
		else if (redir->type == F_APPEND)
			fd = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == F_HERDOC)
		{
			ft_tchek_herdok(redir);
			redir = redir->next;
			continue;
		}
		if (fd < 0)
		{
			perror("Error opening file");
			return (1);
		}
		thcke_fd(fd);
		if (redir->type == FWRITE_OUT || redir->type == F_APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (redir->type == FREAD_IN)
			dup2(fd, STDIN_FILENO);

		ft_closse(redir, fd);
		redir = redir->next;
	}
	return (0);
}

void ft_tchick_slash(char *str_data)
{
	if (ft_strchr(&str_data[0], '/') && access(&str_data[0], X_OK) == -1)
		perror(&str_data[0]);
	else
	{
		if (ft_strcmp(&str_data[0], "ls") == 0)
			printf("Minishell: %s : No such file or directory\n", &str_data[0]);
		else
			printf("Minishell: %s :command not found\n", &str_data[0]);
	}
	exit(127);
}

void ft_tchk_not_peltend(t_data *data, char **env_ar, char *cmd_path)
{

	execve(cmd_path, data->args, env_ar);

	exit(0);
}

int status_res(int status)
{
	if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status) + 128);
	}
	return (WEXITSTATUS(status));
}
int run_cmd(t_data *current, int prev_fd, int *pipe_fd, t_listenv **head)
{
	int status;
	char **env_ar;
	char *cmd_path;
	if (!*head || !head)
		return 0;
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
	if (is_builtin(current, head) == 1)
		return (ft_tchc_data(current, head));
	pid_t pid = fork();
	if (pid == 0)
	{
		env_ar = ft_ar_env(*head);
		if (current->args == NULL)
			exit (0);
		cmd_path = get_command_path(current->args[0], env_ar, &status);
		if (cmd_path == NULL)
			exit(status);
		ft_tchk_not_peltend(current, env_ar, cmd_path);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (status_res(status));
}


int ft_execoshen(t_data *data, t_listenv *head)
{
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	t_data *current = data;

	if (!data || !head)
		return 0;
	if (current->next == NULL)
		return (run_cmd(current, prev_fd, pipe_fd, &head));
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
	int status;
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0);
	
	return status_res(status);
}

