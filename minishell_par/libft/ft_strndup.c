/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:43:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/25 17:14:12 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*copy;
	size_t	i;

	if (!s)
		return (NULL);
	copy = malloc(n + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
