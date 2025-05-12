/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/11 21:04:25 by oelbied          ###   ########.fr       */
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

void tf_tchee_redercter( t_data *current , t_listenv **head)
{
	t_redir	*redir;

  int fd = -1;
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
					redir = redir->next;
				continue;
			}
         if (fd < 0) {
            perror("Error opening file");
            exit(1);
        }
			thcke_fd(fd);
			// ft_echo(current,&head,fd);
			(*head)->fdd = fd;
		// ft_tchc_data(current,&head,head->fdd);
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

void ft_child_proses(t_data *current,int prev_fd, int *pipe_fd,t_listenv **head)
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
              tf_tchee_redercter( current ,head);

			
			env_ar = ft_ar_env(*head);
			cmd_path = get_command_path(current->args[0], env_ar);
			// if (!cmd_path && ft_tchc_data(current, &head ) == 0)
		
				if(ft_strcmp (current->args[0] ,"\"\"") == 0 ||ft_strcmp (current->args[0] ,"\'\'") == 0  )
				{
					printf("Minishell: :command not found\n");
					exit(127);
				}
				else if(!current->args)
				{
				printf("Minishell:%s:command not found\n",current->args[0] );
					exit(127);
					
				}
			if (!cmd_path )
			{
				// ft_putstr_fd("command not found\n",2);
				if(ft_strchr(current->args[0],'/') && access(current->args[0], X_OK) == -1)
				perror(current->args[0] );
				else
				{
					if(ft_strcmp(current->args[0],"ls") == 0)
					printf("Minishell: %s :Permission denied\n", current->args[0]);
					else
					printf("Minishell: %s :No such file or directory\n", current->args[0]);
				}
				exit(127);
			}
			if (ft_strcmp(current->args[0], "echo") == 0)
			{
				if (current->file)
					tf_tchee_redercter(current, head); 

				ft_echo(current, STDOUT_FILENO);
				exit(0); 
			}
			if (ft_tchc_data(current,head,(*head)->fdd) == 0)
			{
				if (access(current->args[0], X_OK) == 0)
				{
					if(execve(current->args[0],current->args,env_ar) == -1)
					{
						printf("%s: is a directory\n",current->args[0]);
						exit(0); 
					}
				}
				else
				execve(cmd_path, current->args,env_ar);
				// if(!cmd_path || access(cmd_path, X_OK) != 0 )
			
				if(ft_strcmp (current->args[0] ,"\0") == 0)
				printf("Minishell: :command not found\n");
				else if(current->args[0] != NULL)
				{
					// printf("Minishell:%s :command not found\n",current->args[0]);
					printf("%s",current->args[0]);
					perror(current->args[0] );
				}
				
				free(cmd_path);
				exit(EXIT_FAILURE);
			}
}

int ft_execoshen(t_data *data, t_listenv *head)
{
    int pipe_fd[2];
    int prev_fd = -1; 
    pid_t pid;
    t_data *current = data;

	// if( data)
	// 	return 0;
    while (current)
    {
        if (current->next && pipe(pipe_fd) == -1)
            ft_erorr("pipe");
        pid = fork();
        if (pid == -1)
			 ft_erorr("fork");
        if (pid == 0)
            ft_child_proses(current,prev_fd,pipe_fd,&head);
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
