/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:13:28 by sidrissi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/28 10:44:54 by sidrissi         ###   ########.fr       */
=======
/*   Updated: 2025/05/26 12:46:18 by oelbied          ###   ########.fr       */
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}
