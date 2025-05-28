/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:32:24 by oelbied           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/28 10:20:19 by sidrissi         ###   ########.fr       */
=======
/*   Updated: 2025/05/28 10:00:25 by oelbied          ###   ########.fr       */
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

<<<<<<< HEAD
	if (NULL == s || 0 == c)
		return (NULL);
=======
	// if (NULL == s || 0 == c)
	// 	return (NULL);

>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
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
