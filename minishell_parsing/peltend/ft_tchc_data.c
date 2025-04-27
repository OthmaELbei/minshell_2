/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tchc_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:41:42 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/24 13:48:04 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_tchc_data(t_data *data,t_listenv *head)
{
	
	if(!ft_strcmp(data->cmd,"env"))
		{
			t_listenv *tamp = head;
			while(tamp){
			printf("%s",tamp->constvrble);
			printf("%s\n",tamp->pat);
			tamp =  tamp->next;
			}
	}
	else if(!ft_strcmp(data->cmd,"pwd"))
		ft_pwd(head);
	else if(!ft_strcmp(data->cmd,"echo"))
		ft_echo(data);
	else if(!ft_strcmp(data->cmd,"unset"))
		ft_unset(data,&head);
	else if(!ft_strcmp(data->cmd,"exit"))
		ft_exit(data);
	else if(!ft_strcmp(data->cmd,"cd"))
		ft_cd(data);
	else if(!ft_strcmp(data->cmd,"export"))
		ft_export(&head ,data);
}
