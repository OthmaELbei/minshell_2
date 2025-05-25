/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:50:17 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/25 19:17:47 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	n_digit(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_fill(char *arr_itoa, long num, int i)
{
	while (i >= 0 && arr_itoa[i] != '-')
	{
		arr_itoa[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (arr_itoa);
}

char	*ft_itoa(int n)
{
	char	*arr_itoa;
	int		len_itoa;
	int		i;
	long	num;

	num = n;
	if (num >= 0)
		len_itoa = n_digit(n);
	else
		len_itoa = n_digit(n) + 1;
	arr_itoa = malloc((len_itoa + 1));
	if (!arr_itoa)
		return (NULL);
	arr_itoa[len_itoa] = '\0';
	if (num < 0)
	{
		arr_itoa[0] = '-';
		num = -num;
	}
	i = len_itoa - 1;
	return (ft_fill(arr_itoa, num, i));
}
