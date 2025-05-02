/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/02 09:31:41 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_cd(t_data *data ,t_listenv *head)
{
	if((getcwd(NULL, 0) == NULL) && (ft_strcmp(data->args[1],"..") == 0 ))
	{
		head->old_env = ft_strjoin(head->old_env,"/");
		head->old_env = ft_strjoin(head->old_env,"..");
	}else if((getcwd(NULL, 0) == NULL) && (ft_strcmp(data->args[1],".") == 0 ))
	{
		head->old_env = ft_strjoin(head->old_env,"/");
		head->old_env = ft_strjoin(head->old_env,".");
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
