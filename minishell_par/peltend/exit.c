/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:40 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/20 17:52:53 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_sing(char c, int *i)
{
	int	sing;

	sing = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sing = -1;
		(*i)++;
	}
	return (sing);
}

int	ft_tchk_long(char *str, long long *out)
{
	unsigned long long	result;
	int					sing;
	int					i;

	i = 0;
	sing = 1;
	result = 0;
	sing = ft_sing(str[0], &i);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if ((sing == 1 && result > (unsigned long long)LLONG_MAX)
			|| (sing == -1 && result > (unsigned long long)LLONG_MAX + 1))
			return (0);
		i++;
	}
	if (sing == 1)
		*out = result * sing;
	else
		*out = result * sing;
	return (1);
}

int	ft_exit(t_data *data)
{
	long long	value;

	if (!ft_strcmp(data->args[0], "exit"))
	{
		if (!data->args[1])
			exit(0);
		if (!ft_tchk_long(data->args[1], &value))
		{
			printf("exit: %s: numeric argument required\n", data->args[1]);
			exit(255);
		}
		if (data->args[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		exit(value % 256);
	}
	return (0);
}
