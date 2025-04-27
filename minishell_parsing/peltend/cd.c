/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/27 19:34:07 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_cd(t_data *data)
{
	// char cwd[1024];
	if(!ft_strcmp(data->cmd, "cd") && data->args[1] ){
		if(chdir(data->args[1]) == -1)
		{
			 printf("%s: No such file or directory\n",data->args[1]);	
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