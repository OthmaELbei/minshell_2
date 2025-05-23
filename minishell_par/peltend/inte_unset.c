/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inte_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:28:20 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/21 15:33:55 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup_unset(char *s)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len && s[i] != '=')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_tchk_value(char *data)
{
	int	i;

	i = 0;
	if (data[i] == '\0')
		return (1);
	if (!ft_isalpha(data[i]) && data[i] != '_')
		return (1);
	i++;
	while (data[i] != '\0')
	{
		if (!ft_isalnum(data[i]) && data[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
