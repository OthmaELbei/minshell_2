/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:13:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/02 11:43:29 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	if (!s1 || !s2)
// 		return (1);
// 	i = 0;
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			break ;
// 		i++;
// 	}
// 	if (s1[i] != s2[i])
// 		return (s1[i] - s2[i]);
// 	return (s1[i] - s2[i]);
// }



#include "../include/minishell.h"

int    ft_strcmp(char *s1, char *s2)
{
    int    i;

    if (!s1 || !s2) // remove an SEGV [ When tab on enter in multiple time ] that's becaus ft_tchc_data send nothing and strcmp don't protect the check null
        return (1); // so we added this line to prevent this SEGV

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