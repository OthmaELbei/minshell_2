/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:22 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/27 21:20:37 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_listenv	*ft_lstnew_env(char *content, char *path)
{
	t_listenv	*new;

	new = (t_listenv *)malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->constvrble = ft_strdup(content);
	new->pat = ft_strdup(path);
	new->next = NULL;
	new->valid = 1;
	return (new);
}
