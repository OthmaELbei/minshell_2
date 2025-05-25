/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/25 09:39:19 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	helper_function(char *delimter, char *line,
// 						int helper_fd, t_listenv *head)
// {
// 	char	**exp;
// 	char	*new_line;
// 	int		n;

// 	new_line = NULL;
// 	exp = NULL;
// 	n = 1377;
// 	if (check_delimter(delimter) == 0)
// 	{
// 		exp = ft_expand_herdoc(line, &n, head);
// 		new_line = exp[0];
// 		write(helper_fd, new_line, ft_strlen(new_line));
// 		write(helper_fd, "\n", 1);
// 	}
// 	else
// 	{
// 		write(helper_fd, line, ft_strlen(line));
// 		write(helper_fd, "\n", 1);
// 	}
// 	(free(line), free(new_line), free(exp));
// }

// void	main_funtion()
// {
	
// }

// int	open_herdoc(char *delimter, char *random_name, int *n, t_listenv *head)
// {
// 	int		fd[2];
// 	char	*line;
// 	char	**exp;
// 	char	*new_delimter;
// 	int		status;

// 	status = 0;
// 	exp = ft_expand_herdoc(delimter, n, head);
// 	new_delimter = exp[0];
// 	random_name = generate_name();
// 	fd[0] = open(random_name, O_RDWR | O_CREAT, 0777);
// 	fd[1] = open (random_name, O_RDONLY | O_CREAT, 0777);
// 	if (unlink(random_name) == -1 || (fd[0] < 0) || (fd[1] < 0))
// 		return (perror("faile"), close(fd[0]), close(fd[1]), -1);
	
// 	main_funtion();
// 	int pid = fork();
// 	if(pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if ((!line) || ft_strcmp(line, new_delimter) == 0)
// 			{
// 				free(line);
// 				close(fd[0]); //????
// 				break ;
// 			}
// 			helper_function(delimter, line, fd[0], head);
// 		}
// 		exit(0);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		waitpid(pid, &status, 0);
// 		if(WIFSIGNALED(status))
// 			return (write(1, "\n", 1), free(random_name), free(exp), free(new_delimter), close(fd[0]), -13);
// 	}
// 	return (free(random_name), free(exp), free(new_delimter), close(fd[0]),
// 		fd[1]); // should close the return file descriptor
// }

// int	ft_herdoc(t_token **tokens, t_listenv *head)
// {
// 	t_token	*current;
// 	int		fd_;
// 	int		n;
// 	char	*random_name;

// 	random_name = NULL;
// 	n = 10;
// 	fd_ = -1;
// 	current = *tokens;
// 	while (current)
// 	{
// 		if (current->type == HERDOC
// 			&& current->next && current->next->type == F_HERDOC)
// 		{
// 			fd_ = open_herdoc(current->next->value[0], random_name, &n, head);
// 			if (fd_ != -1)
// 				current->next->fd = fd_;
// 			// else if (fd_ == -1)
// 				// exit(1);
// 			if (fd_ == -13)
// 				return (-13);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }





// Helper function for heredoc expansion and writing
static void write_heredoc_line(char *delimiter, char *line, int fd, t_listenv *env)
{
	char	**exp;
	char	*new_line;
	int		n;

	n = 1377;
	if (check_delimter(delimiter) == 0)
	{
		exp = ft_expand_herdoc(line, &n, env);
		new_line = exp[0];
		write(fd, new_line, ft_strlen(new_line));
		write(fd, "\n", 1);
		free(new_line);
		free(exp);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
}

// Handles child process for heredoc input
static int handle_heredoc_child(char *delimiter, char *new_delimiter, int fd, t_listenv *env)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, new_delimiter) == 0)
		{
			free(line);
			break;
		}
		write_heredoc_line(delimiter, line, fd, env);
	}
	close(fd);
	exit(0);
}

// Handles parent process for heredoc
static int handle_heredoc_parent(pid_t pid, int fd, char *random_name, char **exp)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		free(random_name);
		free(exp[0]);
		free(exp);
		close(fd);
		write(2, "\n", 1);
		return (-13);
	}
	return (0);
}

// Main heredoc opening function
int	open_herdoc(char *delimter, char *random_name, int *n, t_listenv *head)
{
	int		fd[2];
	char	**exp;
	pid_t	pid;
	int		status;

	exp = ft_expand_herdoc(delimter, n, head);
	random_name = generate_name();
	fd[0] = open(random_name, O_RDWR | O_CREAT, 0777);
	fd[1] = open(random_name, O_RDONLY | O_CREAT, 0777);
	if (unlink(random_name) == -1 || fd[0] < 0 || fd[1] < 0)
		return (perror("failed"), close(fd[0]), close(fd[1]), -1);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(delimter, exp[0], fd[0], head);
	else
	{
		status = handle_heredoc_parent(pid, fd[0], random_name, exp);
		if (status != 0)
			return (close(fd[1]), status);
	}
	free(random_name);
	free(exp[0]);
	free(exp);
	close(fd[0]);
	return (fd[1]);
}

// Original ft_herdoc remains unchanged
int	ft_herdoc(t_token **tokens, t_listenv *head)
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
		if (current->type == HERDOC && current->next && current->next->type == F_HERDOC)
		{
			fd_ = open_herdoc(current->next->value[0], random_name, &n, head);
			if (fd_ != -1)
				current->next->fd = fd_;
			if (fd_ == -13)
				return (-13);
		}
		current = current->next;
	}
	return (0);
}
