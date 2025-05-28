/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:32:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/28 10:20:19 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	if (NULL == s || 0 == c)
		return (NULL);
	i = 0;
	d = (char )c;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return (((char *)s + i));
		i++;
	}
	if (s[i] == d)
		return (((char *)s + i));
	return (NULL);
}
