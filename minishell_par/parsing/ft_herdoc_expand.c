/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:54:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/20 13:25:40 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_dollar_herdoc(t_expand *ex, char *str,
							int *flag, t_listenv *head)
{
	ex->dollar_count = 0;
	while (str[ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars_herdoc(ex, str, flag, head);
}

void	handle_quote_herdoc(t_expand *ex, char *str, int *flag,
							t_listenv *head)
{
	if (*flag == 10)
	{
		ex->i++;
		while (str[ex->i] && (str[ex->i] != '"' && str[ex->i] != '\''))
		{
			append_char_herdoc(ex, str[ex->i]);
			ex->i++;
		}
		if (str[ex->i] == '"' || str[ex->i] == '\'')
			ex->i++;
	}
	else
	{
		while (str[ex->i])
		{
			if (str[ex->i] == '$' && *flag != 10)
				process_dollar_herdoc(ex, str, flag, head);
			else
			{
				append_char_herdoc(ex, str[ex->i]);
				ex->i++;
			}
		}
	}
}

char	**split_herdoc(t_expand *ex, int *flag)
{
	char	**result;

	if (*flag == 0)
	{
		result = ft_split(ex->res, ' ');
		free(ex->res);
	}
	else
	{
		result = malloc(2 * sizeof(char *));
		if (!result)
		{
			free(ex->res);
			return (NULL);
		}
		result[0] = ex->res;
		result[1] = NULL;
	}
	return (result);
}

char	**ft_expand_herdoc(char *str, int *flag, t_listenv *head)
{
	t_expand	ex;

	ft_memset(&ex, 0, sizeof(ex));
	ex.res = ft_strdup("");
	if (!ex.res)
		return (NULL);
	while (str[ex.i])
	{
		if (str[ex.i] == '"' || str[ex.i] == '\'')
			handle_quote_herdoc(&ex, str, flag, head);
		else if (str[ex.i] == '$' && *flag != 10)
			process_dollar_herdoc(&ex, str, flag, head);
		else
			(append_char_herdoc(&ex, str[ex.i]), ex.i++);
	}
	return (split_herdoc(&ex, flag));
}
