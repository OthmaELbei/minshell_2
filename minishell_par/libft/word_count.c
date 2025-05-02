/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:13 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/30 16:40:54 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_sep(char s, char c)
{
	return (s == c);
} 

int	word_count(char *s, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(s[i], c))
		{
			words++;
			while (s[i] && !is_sep(s[i], c))
				i++;
		}
		else
			i++; 
	}
	return (words);
}