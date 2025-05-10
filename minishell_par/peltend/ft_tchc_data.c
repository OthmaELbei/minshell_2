/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tchc_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:41:42 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/10 13:08:57 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_tchc_data(t_data *data,t_listenv **head ,int fd )
{

	if(!data || !head)
	 return 0;
	    //  printf("ft_tchc_data called with command: %s\n", data->cmd);
	if(!ft_strcmp(data->cmd,"env"))
		{
			t_listenv *tamp = *head;
			while(tamp){
			printf("%s",tamp->constvrble);
			printf("%s\n",tamp->pat);
			tamp =  tamp->next;
			// return 1;
			}
	}
	else if(!ft_strcmp(data->cmd,"pwd"))
		return (ft_pwd(*head),1);
	else if(!ft_strcmp(data->cmd,"echo"))
		return (ft_echo(data,fd),1);
	else if(!ft_strcmp(data->cmd,"unset"))
		return (ft_unset(data,head),1);
	else if(!ft_strcmp(data->cmd,"exit"))
		return (ft_exit(data),1);
	else if(!ft_strcmp(data->cmd,"cd"))
		return (ft_cd(data,*head),1);
	else if(!ft_strcmp(data->cmd,"export"))
		return (ft_export(*head ,data),1);
	return 0;
}
