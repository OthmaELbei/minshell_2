/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/10 13:08:45 by oelbied          ###   ########.fr       */
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



void ft_echo(t_data *data, int fd )
{
    int i = 1;
    int newline = 1;
    if(!data)
	return ;
    if (!data || !data->args || !data->args[0])
        return;
	
 if (data->args[1] && !ft_strcmp(data->args[1], "-n"))
        {
            newline = 0;
            i = 2;
        }

        while (data->args[i])
        {
            // printf("%s", data->args[i]);
      
			
			ft_putstr_fd(data->args[i],fd);
            i++;
            if (data->args[i])
              	ft_putstr_fd(" ",fd);
        }

        if (newline)
          	ft_putstr_fd("\n",fd);
    
}
