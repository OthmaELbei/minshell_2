/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excoshen_n_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:23:41 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/25 17:43:15 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_freee(char **arrai)
{
	int i;
	i = 0;
	if (!arrai)
		return;
	while (arrai[i])
		free(arrai[i++]);
	free(arrai);
}

char *ft_tcheck_path(char *commnd)
{
	if (!commnd)
		return (NULL);
	if (ft_strchr(commnd, '/'))
	{
		if (access(commnd,X_OK) == 0)
			return (ft_strdup(commnd));
	}
	return (NULL);
}

char *serch_path(char **envp)
{
	int i;

	i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			 return (envp[i] + 5);
		i++;
	}
	
   return (NULL);
}

char *make_path(char **all_path, char *commnd)
{
	char *temp_path;
	char *full_path;
	int		i;

	i = 0;
	while(all_path[i])
	{
		temp_path = ft_strjoin (all_path[i], "/");
		full_path = ft_strjoin (temp_path, commnd);
		free(temp_path);

		if (access(full_path, X_OK) == 0)
			return (full_path);
		free (full_path);
		i++;
	}
	return (NULL);
}

char *get_command_path(char *commnd, char **ary_envp)
{
	char	**all_path;
	char	*cmd_path;
	char 	*strn_path;
	int		i;

	i = 0;
	cmd_path = ft_tcheck_path(commnd);
	if (cmd_path)
		return (cmd_path);
	strn_path = serch_path(ary_envp);
	if (!strn_path)
		return (NULL);
	all_path = ft_split(strn_path,':');
	if (!all_path)
		return (NULL);
	cmd_path = make_path(all_path,commnd);
	ft_freee(all_path);
	return (cmd_path);
}
