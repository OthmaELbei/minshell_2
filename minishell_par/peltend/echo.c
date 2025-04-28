/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/28 19:15:52 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void ft_echo(t_data *data,t_listenv *head)
// {
// 	int i = 2;
// 	int j = 1;
// 	if (!data || !data->args || !data->args[0])
//         return;
// 	tchck_head(head);
	
// // void(*head);
// 	if (!ft_strcmp(data->args[0],"echo") && !ft_strcmp(data->args[1],"-n"))
// 	{
//         while (data->args[i] != NULL)
// 		{
// 			printf("%s",data->args[i]);
// 			i++;
// 			if( data->args[i] != NULL)
// 				printf(" ");
// 		}		
// 	}
// 	else if(!ft_strcmp(data->args[0],"echo") )
// 	{	
// 		while (data->args[j] != NULL) 
// 		{
// 			printf("%s",data->args[j]);
// 			j++;
// 				if(data->args[j] != NULL)
// 					printf(" ");
// 		}
// 	 	printf("\n");
// 	}else 
// 	{
// 		 	printf("\n");
// 	}
// }

// void ft_echo(t_data *data,t_listenv *head)
// {
// 	int i = 2;
// 	int j = 1;
// 	if (!data || !data->args || !data->args[0])
//         return;
//   if(tchck_head(data,head))
//   {
//  	 printf("\n");
// 	return ;
//   }
// // void(*head);
// 	if (!ft_strcmp(data->args[0],"echo") && !ft_strcmp(data->args[1],"-n"))
// 	{
//         while (data->args[i] != NULL)
// 		{
// 			printf("%s",data->args[i]);
// 			i++;
// 			if( data->args[i] != NULL)
// 				printf(" ");
// 		}		
// 	}
// 	else if(!ft_strcmp(data->args[0],"echo") )
// 	{	
// 		while (data->args[j] != NULL) 
// 		{
// 			printf("%s",data->args[j]);
// 			j++;
// 				if(data->args[j] != NULL)
// 					printf(" ");
// 		}
// 	 	printf("\n");
// 	}else 
// 	{
// 		 	printf("\n");
// 	}
// }
int tchck_head(t_data *data,t_listenv *head)
{
    if (!head)
        return 1;

    // t_listenv *cont = head;
	// while(cont)
	// {
	// 	printf("%s%s\n",cont->constvrble,cont->pat);
	// 	cont = cont->next;
	// }
		
    while (head)
    {
		if(!ft_strcmp (data->args[1] , head->pat))
		{
			// printf("%s",data->args[1]);
			printf("%s++++++++++++++++",head->pat);
        return 1 ;
		}
        head = head->next;
    }
	
	return 0;
}
void ft_echo(t_data *data,t_listenv **head)
{
    int i = 1;
    int newline = 1;
    if(!data)
	return ;
    if (!data || !data->args || !data->args[0])
        return;
	if(tchck_head(data, *head))
	{
		printf("\n");
	}
 if (data->args[1] && !ft_strcmp(data->args[1], "-n"))
        {
            newline = 0;
            i = 2;
        }

        while (data->args[i])
        {
            printf("%s-------", data->args[i]);
            i++;
            if (data->args[i])
                printf(" ");
        }

        if (newline)
            printf("\n");
    
}
