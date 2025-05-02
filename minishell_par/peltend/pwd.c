/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:59:09 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/01 17:33:34 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void tchkin(t_listpwd *data)
// {
// 		t_listpwd *timp = malloc(sizeof(t_listpwd));
//      if(!timp)
// 	 	return ;
// 	timp->data = getpwd("PWD");
	
// }
void ft_pwd(t_listenv *head)
{
	if(getcwd(NULL, 0) == NULL)
	{
		if(head->old_env == NULL)
		printf("%s\n",getenv("PWD"));
		else
		{
			printf("%s\n",head->old_env);
		}
	}
		else
		{
		
			printf("%s\n",getcwd(NULL, 0));
			head->old_env = getcwd(NULL, 0);
		}
	// if(getcwd(NULL, 0) == NULL)
	// {
	// 	printf("%s",timp->data);
	// 	free(timp);
	// 	return;
	// 	// while (head)
	// 	// {
	// 	// 	if(ft_strcmp(head->constvrble,"OLDPWD=") == 0)
	// 	// 	{
	// 	// 		printf("%s",head->pat);
	// 	// 	}
	// 	// 	head = head->next;
	// 	// }
	// }else 
	// {
	// 	timp->data = getcwd(NULL, 0);
	// 	printf("%s\n" ,getcwd(NULL, 0) );
	// }
}

