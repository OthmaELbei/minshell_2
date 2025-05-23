/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/23 14:14:14 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	comend_cd(t_data *data)
{
	char	*home;

	if (data->args[1])
	{
		if (chdir(data->args[1]) == -1)
		{
			perror(data->args[1]);
			return (1);
		}
	}
	else
	{
		home = getenv("HOME");
		if (!home || chdir(home) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_data *data, t_listenv *head)
{
	char	*cwd;
	char	*temp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL && (ft_strcmp(data->args[1], "..") == 0
			|| ft_strcmp(data->args[1], ".") == 0))
	{
		perror("cd: error retrieving current directory:\
getcwd: cannot access parent directories");
		temp = ft_strjoin(head->old_pwd, "/");
		if (!temp)
			return (1);
		free(head->old_pwd);
		head->old_pwd = ft_strjoin(temp, data->args[1]);
		free(temp);
	}
	else if (cwd != NULL)
	{
		free(head->old_pwd);
		head->old_pwd = ft_strdup(cwd);
		free(cwd);
	}
	comend_cd(data);
	return (0);
}
