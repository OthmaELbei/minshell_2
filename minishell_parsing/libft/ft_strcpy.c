/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:46:26 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/26 09:12:10 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dst, const char *src,int i)
{
	int d;

	d = 0;
	while (src[i] != '\0')
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[i] = '\0';
	return (dst);
}
