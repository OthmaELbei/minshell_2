/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:30:47 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/28 10:48:30 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_err(char *error, char *value, t_keyword type, int count)
{
	if (type == APPEND && count == 3)
		printf("%s `>'\n", ERROR);
	if (type == APPEND && count > 3)
		printf("%s `>>'\n", ERROR);
	if (type == HERDOC && count == 3)
		printf("%s `newline'\n", ERROR);
	if (type == HERDOC && count == 4)
		printf("%s `<'\n", ERROR);
	if (type == HERDOC && count == 5)
		printf("%s `<<'\n", ERROR);
	if (type == HERDOC && count > 5)
		printf("%s `<<<'\n", ERROR);
}
