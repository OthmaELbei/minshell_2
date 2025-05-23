/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/19 14:26:18 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tche_n_tow_flag(char **args, int i, int *j, int *flag)
{
	if (!args[i])
		return (1);
	while (args[i][*j] != '\0')
	{
		if (args[i][*j] != 'n')
		{
			if (args[i][*j] == 'e')
				(*j)++;
			else
			{
				if (!(args[1] && args[1][0] == '-'
					&& args[1][1] == 'n' && i > 1))
					*flag = 0;
				return (1);
			}
		}
		else
			(*j)++;
	}
	return (0);
}

int	ft_check_n_flag(char **args, int *i)
{
	int	flag;
	int	newline;
	int	j;

	flag = 0;
	newline = 0;
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
	{
		flag = 1;
		while (args[*i] && !newline && args[*i][0] == '-' && args[*i][1] == 'n')
		{
			j = 2;
			newline = ft_tche_n_tow_flag(args, *i, &j, &flag);
			(*i)++;
		}
	}
	if (newline == 1)
		(*i)--;
	return (flag);
}

void	ft_print_echo_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
}

int	ft_echo(t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	if (!data || !data->args || !data->args[0])
		return (0);
	flag = ft_check_n_flag(data->args, &i);
	ft_print_echo_args(data->args, i);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
