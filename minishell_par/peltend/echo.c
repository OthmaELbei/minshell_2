/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/11 11:03:42 by oelbied          ###   ########.fr       */
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
    int newline = 0;
    int flag = 0;
    if (!data || !data->args || !data->args[0])
        return;
	
 		if (data->args[1] && data->args[1][0] ==  '-' && data->args[1][1] ==  'n')
        {
			flag = 1;
				int j = 1;
			while(data->args[i] && !newline && data->args[i][0] == '-' && data->args[i][1] == 'n')
		{
			j = 2;
			while(data->args[i][j] != '\0' )
			{
				
					if(data->args[i][j] != 'n' )
					{
						 if(data->args[i][j] ==  'e')
						 {
							j++; 
							
						 }
							else
							{
								newline = 1;
								if(!(data->args[1][0] ==  '-' && data->args[1][1] ==  'n' && i > 1))
								 flag = 0;
								break;
							}
					}
				j++;
			}
			i++;
		}
        }
	if(newline == 1)
		 i -= 1;

        while (data->args[i])
        {
            // printf("%s", data->args[i]);
      
			
			ft_putstr_fd(data->args[i],fd);
            i++;
            if (data->args[i])
              	ft_putstr_fd(" ",fd);
        }
     
        if (!flag)
          	ft_putstr_fd("\n",fd);
    
}
