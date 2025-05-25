/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:02:42 by sidrissi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/24 16:23:17 by sidrissi         ###   ########.fr       */
=======
/*   Updated: 2025/05/25 17:12:06 by oelbied          ###   ########.fr       */
>>>>>>> 8c3f579ca55784838cec2171d5c8efae4af4a915
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

<<<<<<< HEAD
    i = 0;
    if (NULL == s)
        return (-1);
    while (s[i])
        i++;
    return (i);
}
=======
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}
>>>>>>> 8c3f579ca55784838cec2171d5c8efae4af4a915
