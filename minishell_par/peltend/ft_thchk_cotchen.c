/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thchk_cotchen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:01:36 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/21 15:35:35 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_tchk_cotachen( char *s1)
{
	size_t	len;
	char	*str_pt;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + 1;
	str_pt = (char *)malloc((len) * sizeof(char));
	if (str_pt == NULL)
	{
		return (NULL);
	}
	while (len > i)
	{
		if (s1[i] != '\"')
		{
			str_pt[j] = s1[i];
			j++;
		}
		i++;
	}
	return (str_pt);
}
