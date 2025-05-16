/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:03:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/16 09:35:55 by oelbied          ###   ########.fr       */
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

void tf_tchee_redercter( t_data *data , t_listenv **head)
{
	t_redir	*redir;

  	int fd = -1;
	redir = data->file;
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

void ft_tchick_slash(char *str_data)
{
					if(ft_strchr(&str_data[0],'/') && access(&str_data[0], X_OK) == -1)
				perror(&str_data[0] );
				else
				{
					if(ft_strcmp(&str_data[0],"ls") == 0)
					printf("Minishell: %s : No such file or directory\n",&str_data[0]);
					else
					printf("Minishell: %s :command not found\n", &str_data[0]);
				}
				exit(127);
}

void ft_tchk_not_peltend(t_data *data,char **env_ar,char *cmd_path)
{
					if (access(data->args[0], X_OK | F_OK) == 0)
				{
					if(execve(data->args[0],data->args,env_ar) == -1)
					{
						printf("Minishell: %s: is a directory\n",data->args[0]);
						exit(0); 
					}
				}
				else
				{
				execve(cmd_path, data->args,env_ar);
				}
				// if(!cmd_path || access(cmd_path, X_OK) != 0 )
			
				if(ft_strcmp (data->args[0] ,"\0") == 0)
				printf("Minishell: :command not found\n");
				else if(data->args[0] != NULL)
					perror(data->args[0] );
				// free(cmd_path);
				exit(EXIT_FAILURE);
}


void ft_child_proses(t_data *current,int prev_fd, int *pipe_fd,t_listenv **head)
{
	char **env_ar;
	char *cmd_path;
 	if(!*head || !head)
 		return ;
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
			
            if ( current->file)
              tf_tchee_redercter( current ,head);
				env_ar = ft_ar_env(*head);
				if(current->args ==  NULL)
				 return ;
				cmd_path = get_command_path(current->args[0], env_ar);		
				if(!current->args || !current->args[0])
				{
				printf("Minishell:%s:command not found\n",current->args[0] );
					exit(127);	
				}
				else if(ft_strcmp (current->args[0] ,"\"\"") == 0 ||ft_strcmp (current->args[0] ,"\'\'") == 0  )
				{
					printf("Minishell: :command not found\n");
					exit(127);
				}
				
			if (!cmd_path )
				ft_tchick_slash(current->args[0]);
			if (ft_strcmp(current->args[0], "echo") == 0)
			{
				ft_echo(current, STDOUT_FILENO);
				exit(0); 
			}
			if (ft_tchc_data(current,head,(*head)->fdd) == 0)
				ft_tchk_not_peltend(current,env_ar,cmd_path);
}

int ft_execoshen(t_data *data, t_listenv *head)
{
    int pipe_fd[2];
    int prev_fd = -1; 
    pid_t pid;
    t_data *current = data;

	if( !data || !head)
		return 0;
    while (current)
    {
        if (current->next && pipe(pipe_fd) == -1)
            ft_erorr("pipe");

		if( data->next)
		{
			pid = fork();
			if (pid == -1)
				ft_erorr("fork");
			if (pid == 0)
				ft_child_proses(current,prev_fd,pipe_fd,&head);
		}
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
