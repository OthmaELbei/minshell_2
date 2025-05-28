/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:39:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/26 11:37:59 by sidrissi         ###   ########.fr       */
=======
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:39:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/26 10:23:19 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/05/25 19:16:45 by oelbied          ###   ########.fr       */
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	cc;

	s = (unsigned char *)b;
	cc = (unsigned char)c;
	while (len--)
	{
		s[len] = cc;
	}
	return (b);
}
