/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:59:09 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/25 19:04:08 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_listenv *head)
{
	char	*cwd;

	(void)head;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		if (store_pwd(NULL, 3))
			printf("%s\n", store_pwd(NULL, 0));
		return (0);
	}
	else
	{
		printf("+++++++++++++++++\n");
		printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
