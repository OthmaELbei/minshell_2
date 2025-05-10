/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/10 15:32:17 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int ft_cd(t_data *data ,t_listenv *head)
{

	// char cwd[1024];
	// if(getcwd(NULL, 0) == NULL)
	if((getcwd(NULL, 0) == NULL) && (ft_strcmp(data->args[1],"..") == 0 ))
	{
		 perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		
		head->old_pwd = ft_strjoin(head->old_pwd,"/");
		head->old_pwd = ft_strjoin(head->old_pwd,"..");
		
	}else if((getcwd(NULL, 0) == NULL) && (ft_strcmp(data->args[1],".") == 0 ))
	{
		// perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		head->old_pwd = ft_strjoin(head->old_pwd,"/");
		head->old_pwd = ft_strjoin(head->old_pwd,".");
	}
	if(!ft_strcmp(data->cmd, "cd") && data->args[1] ){
		if(chdir(data->args[1]) == -1)
		{
			 printf("%s: No such \n",data->args[1]);	
			 return 1;
		}
	}
	if(!ft_strcmp(data->cmd, "cd") && !data->args[1])
	{
		if(chdir(getenv("HOME")) ==  -1)
		{
			perror("chdir failed");
		}
	} 
    return 0;
}

