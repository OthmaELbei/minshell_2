/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:57:28 by sidrissi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/28 10:46:00 by sidrissi         ###   ########.fr       */
=======
/*   Updated: 2025/05/26 12:49:02 by oelbied          ###   ########.fr       */
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
