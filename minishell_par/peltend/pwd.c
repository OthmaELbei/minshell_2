/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:59:09 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/16 09:15:14 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_pwd(t_listenv *head)
{
	if( getcwd(NULL, 0) == NULL)
	{
		if(head->old_pwd == NULL)
		
		head->old_pwd = getenv("pwd");
		if(head->old_pwd == NULL)
		return ;
		else
		printf("%s\n",head->old_pwd);
		
	}
	else
	{
		head->old_pwd = getcwd(NULL,0);
		printf("%s\n",head->old_pwd);
	}
}
