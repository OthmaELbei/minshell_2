/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/16 09:22:28 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void ft_echo(t_data *data, int fd )
// {
//     int i = 1;
//     int newline = 0;
//     int flag = 0;
//     if (!data || !data->args || !data->args[0])
//         return;
	
//  		if (data->args[1] && data->args[1][0] ==  '-' && data->args[1][1] ==  'n')
//         {
// 			flag = 1;
// 				int j = 1;
// 			while(data->args[i] && !newline && data->args[i][0] == '-' && data->args[i][1] == 'n')
// 		{
// 			j = 2;
// 			while(data->args[i][j] != '\0' )
// 			{
				
// 					if(data->args[i][j] != 'n' )
// 					{
// 						 if(data->args[i][j] ==  'e')
// 						 {
// 							j++; 
							
// 						 }
// 							else
// 							{
// 								newline = 1;
// 								if(!(data->args[1][0] ==  '-' && data->args[1][1] ==  'n' && i > 1))
// 								 flag = 0;
// 								break;
// 							}
// 					}
// 				j++;
// 			}
// 			i++;
// 		}
//         }
// 	if(newline == 1)
// 		 i -= 1;

//         while (data->args[i])
//         {
      
// 			if(ft_strcmp(data->args[i],"\"\"") == 0 ||ft_strcmp(data->args[i],"\'\'") == 0)
// 			{
// 				ft_putstr_fd("",fd);
// 			}else
// 			ft_putstr_fd(data->args[i],fd);
//             i++;
//             if (data->args[i])
//               	ft_putstr_fd(" ",fd);
//         }
     
//         if (!flag)
//           	ft_putstr_fd("\n",fd);
    
// }

int ft_tche_n_tow_flag(char  **args, int i , int *j,  int *flag)
{
	if(!args[i])
	 return 1;
	    while (args[i][*j] != '\0')
            {
                if (args[i][*j] != 'n')
                {
                    if (args[i][*j] == 'e')
                        (*j)++;
                    else
                    {
                        if (!( args[1] && args[1][0] == '-' && args[1][1] == 'n' && i > 1))
                            *flag = 0;
                       return 1;
                    }
                }else
                (*j)++;
            }
			return 0;
}
int ft_check_n_flag(char **args, int *i)
{
    int flag = 0;
    int newline = 0;
    int j;

    if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
    {
        flag = 1;
        while (args[*i] && !newline && args[*i][0] == '-' && args[*i][1] == 'n')
        {
            j = 2;
       newline = ft_tche_n_tow_flag(args, *i , &j,  &flag);
            (*i)++;
        }
    }
    if (newline == 1)
        (*i)--;

    return flag;
}
void ft_print_echo_args(char **args, int i, int fd)
{
    while (args[i])
    {
        // if (ft_strcmp(args[i], "\"\"") == 0 || ft_strcmp(args[i], "\'\'") == 0)
        // {
        //     ft_putstr_fd("", fd);
        // }
        // else
        // {
            ft_putstr_fd(args[i], fd);
        // }
        i++;
        if (args[i])
            ft_putstr_fd(" ", fd);
    }
}


void ft_echo(t_data *data, int fd)
{
    int i = 1;
    int flag;

    if (!data || !data->args || !data->args[0])
        return;

    flag = ft_check_n_flag(data->args, &i);
    ft_print_echo_args(data->args, i, fd);

    if (!flag)
        ft_putstr_fd("\n", fd);
}