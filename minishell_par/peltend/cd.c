/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/25 19:03:49 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*store_pwd(char *str, int flag)
{
	static char	*pwd;
	char		*cwd;
	char		*tmp;

	if (flag == 1)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			tmp = ft_strdup(cwd);
			free(cwd);
			free(pwd);
			pwd = tmp;
		}
	}
	if (flag == 2 && pwd)
	{
		tmp = ft_strjoin(pwd, str);
		if (tmp)
		{
			free(pwd);
			pwd = tmp;
		}
	}
	return (pwd);
}

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
	store_pwd(NULL, 1);
	return (0);
}

int	ft_cd(t_data *data, t_listenv *head)
{
	char	*cwd;

	(void)head;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL && (ft_strcmp(data->args[1], "..") == 0
			|| ft_strcmp(data->args[1], ".") == 0))
	{
		perror("cd: error retrieving current directory:\
getcwd: cannot access parent directories");
		store_pwd("/", 2);
		store_pwd(data->args[1], 2);
	}
	comend_cd(data);
	free(cwd);
	return (0);
}
