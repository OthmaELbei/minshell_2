/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/01 12:55:50 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void thcke_fd( int fd)
{
	 if (fd == -1)
	{
			perror("open");
			exit(EXIT_FAILURE);
	}
}
void ft_closse(t_redir *redir, int fd)
{
    if (redir->type == FWRITE_OUT || redir->type == FREAD_IN || redir->type == F_APPEND)
    {
        thcke_fd(fd);
        close(fd);
    }
}

void ft_tchek_herdok(t_redir *redir)
{
	dup2(redir->fd,STDIN_FILENO);
	close(redir->fd);
	redir = redir->next;
}
void ft_erorr(char *str)
{
	 perror(str);
     exit(EXIT_FAILURE);
}
void tf_tchee_redercter( t_data *current)
{
	t_redir	*redir;
	int		fd;

	redir = current->file;
		while (redir)
		{
			if (redir->type == FWRITE_OUT)
				fd = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (redir->type == FREAD_IN)
				fd = open(redir->name,O_RDONLY);
			else if (redir->type == F_APPEND)
				fd = open(redir->name,O_CREAT | O_WRONLY | O_APPEND,0644);
			else if(redir->type == F_HERDOC)
			{
				ft_tchek_herdok(redir);
				continue;
			}
			thcke_fd(fd);
		  	if (redir->type == FWRITE_OUT || redir->type == F_APPEND) 
            dup2(fd, STDOUT_FILENO);
    		 else if (redir->type == FREAD_IN)
            dup2(fd, STDIN_FILENO);
			ft_closse(redir, fd);
			redir = redir->next;
		}
}

void ft_close_pip(int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
}

void ft_child_proses(t_data *current,int prev_fd, int *pipe_fd,t_listenv *head)
{
	char **env_ar;
	char *cmd_path;
	
	if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (current->next)
               ft_close_pip(pipe_fd);
            if ( current->file)
              tf_tchee_redercter( current);
			env_ar = ft_ar_env(head);
			cmd_path = get_command_path(current->args[0], env_ar);
			if (!cmd_path)
			{
				exit(127);
			}
			execve(cmd_path, current->args,env_ar);
			perror("execve");
			free(cmd_path);
			exit(EXIT_FAILURE);
            perror("execvp");
            exit(EXIT_FAILURE);
}

int ft_execoshen(t_data *data, t_listenv *head)
{
    int pipe_fd[2];
    int prev_fd = -1; 
    pid_t pid;
    t_data *current = data;

    while (current)
    {
        if (current->next && pipe(pipe_fd) == -1)
            ft_erorr("pipe");
        pid = fork();
        if (pid == -1)
			 ft_erorr("fork");
        if (pid == 0)
            ft_child_proses(current,prev_fd,pipe_fd,head);
        if (prev_fd != -1)
            close(prev_fd); 
        if (current->next)
        {
            close(pipe_fd[1]);       
            prev_fd = pipe_fd[0];   
        }
        current = current->next;
    }
    while (wait(NULL) > 0);
    return 0;
}
