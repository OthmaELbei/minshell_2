/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tchcke_pluss.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:42:53 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/28 14:55:03 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  thcking_pluss(char *str)
{
	int i = 0;
	while(str[i]  !=  '\0')
	{
		
		if(str[i] == '+' && str[i + 1] == '=')
		{
			return 1;
		}
		else if(str[i] == '+' && str[i + 1] != '=')
		{
			printf("'%s':not a valid identifier\n",str);
			return 0;
		}
		i++;
	}
	return 1;
}
int tchking_egal(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if( str[i - 1] != '+' && str[i] == '=' )
		{
			return 1;
		}
		i++;
	}
	return 0;
}
// int main()
// {
// 	char *str = "jks+j";
// 	if(thcking_pluss(str))
// 	{
// 		printf(" that is here");
// 	}else {
// 		printf("that is not here");
// 	}
// }