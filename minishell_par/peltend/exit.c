/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:40 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/28 14:55:03 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_tchk_long(char *str, long long *out)
{
	int sing;

	sing = 1;
	int i = 0;
	unsigned long long result = 0;
	
	if(str[0] ==  '-' || str[0] == '+')
	{
		if(str[i] == '-')
		{
			sing = -1;
		}
		i++;
	}
	while (str[i]) {
		if (!ft_isdigit(str[i]))
			return 0;
		result = result * 10 + (str[i] - '0');

		if ((sing == 1 && result > (unsigned long long)LLONG_MAX) ||
		    (sing == -1 && result > (unsigned long long)LLONG_MAX + 1))
			return 0;
		i++;
	}
	if(sing == 1)
	*out = result * sing;
	else
	*out = result * sing;
   return 1;
}
int ft_exit(t_data *data)
{
    // char input[100];
   long long value;
    // char *input = readline("Enter command: ");
	// char **str = ft_split(input , ' ');
	if( !ft_strcmp(data->args[0], "exit"))
	{
		if(!data->args[1])
			exit(0);
		if( !ft_tchk_long(data->args[1], &value))
		{
			printf("exit: %s: numeric argument required\n",data->args[1]);
			exit(255);
		}
		if( data->args[2])
		{
			printf("exit: too many arguments\n");
			return 1;
		}
		exit(value % 256);
	}
    return 0;
}
