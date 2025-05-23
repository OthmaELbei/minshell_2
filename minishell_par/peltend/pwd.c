/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:59:09 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/23 10:30:21 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	ft_pwd(t_listenv *head)
// {
// 	char	*tmp;
// 	char	*cwd;

// 	cwd = getcwd(NULL, 0);
// 	if (cwd == NULL)
// 	{
// 		if (head->old_pwd == NULL)
// 			head->old_pwd = getenv("pwd");
// 		if (head->old_pwd == NULL)
// 			return (0);
// 		else
// 			printf("%s\n", head->old_pwd);
// 	}
// 	else
// 	{
// 		printf("+++++++++++++++++\n");
// 		printf("%s\n", cwd);
// 		tmp = head->old_pwd ;
// 		head->old_pwd = cwd;
// 		if (!tmp)
// 			free(tmp);
// 	}
// 	return (0);
// }
int	ft_pwd(t_listenv *head)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (head->old_pwd)
			printf("%s\n", head->old_pwd);
		else
			perror("pwd");
	}
	else
	{
		printf("%s\n", cwd);
		free(head->old_pwd);
		head->old_pwd = ft_strdup(cwd);
		free(cwd);
	}
	return (0);
}
