/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tchc_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:41:42 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 14:33:43 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_env(t_listenv **head)
{
	t_listenv	*tamp;

	tamp = *head;
	while (tamp)
	{
		if (ft_strchr(tamp->constvrble, '='))
		{
			printf("%s", tamp->constvrble);
			printf("%s\n", tamp->pat);
		}
		tamp = tamp->next;
	}
	return (0);
}

int	ft_tchc_data(t_data *data, t_listenv **head)
{
	if (!data || !head || !*head)
		return (0);
	if (!ft_strcmp(data->cmd, "env"))
		return (print_env(head));
	else if (!ft_strcmp(data->cmd, "pwd"))
		return (ft_pwd(*head));
	else if (!ft_strcmp(data->cmd, "echo"))
		return (ft_echo(data));
	else if (!ft_strcmp(data->cmd, "unset"))
		return (ft_unset(data, head));
	else if (!ft_strcmp(data->cmd, "exit"))
		return (ft_exit(data));
	else if (!ft_strcmp(data->cmd, "cd"))
		return (ft_cd(data, *head));
	else if (!ft_strcmp(data->cmd, "export"))
		return (ft_export(*head, data));
	return (0);
}

int	is_builtin(t_data *data, t_listenv **head)
{
	if (!data || !head || !*head)
		return (0);
	if (!ft_strcmp(data->cmd, "env"))
		return (1);
	else if (!ft_strcmp(data->cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(data->cmd, "echo"))
		return (1);
	else if (!ft_strcmp(data->cmd, "unset"))
		return (1);
	else if (!ft_strcmp(data->cmd, "exit"))
		return (1);
	else if (!ft_strcmp(data->cmd, "cd"))
		return (1);
	else if (!ft_strcmp(data->cmd, "export"))
		return (1);
	return (0);
}
