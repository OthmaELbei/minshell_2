/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:29:27 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/30 11:45:14 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_double_quote(t_expand *ex, char *str, t_listenv *head, t_keyword type)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '"')
	{
		if (str[ex->i] == '$' && type != F_HERDOC)
		{
			process_dollar(ex, str, head, type);
		}
		else
		{
			append_char(ex, str[ex->i]);
			ex->i++;
		}
	}
	if (str[ex->i] == '"')
		ex->i++;
}

char **split(t_expand *ex)
{
	char **result;

	if (ex->flag == 0)
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

char **expand_string(char *str, t_listenv *head, t_keyword type)
{
	t_expand ex;

	ft_memset(&ex, 0, sizeof(ex));
	ex.res = ft_strdup("");
	if (!ex.res)
		return (NULL);
	while (str[ex.i])
	{
		if (str[ex.i] == '\'')
		{
			ex.flag = 2; //you don't need it for ambigous
			handle_single_quote(&ex, str); // change the vlage for ambgious
		}
		else if (str[ex.i] == '"')
		{
			ex.flag = 1;
			handle_double_quote(&ex, str, head, type);
		}
		else if (str[ex.i] == '$' && type != F_HERDOC)
			process_dollar(&ex, str, head, type);
		else
			(append_char(&ex, str[ex.i]), ex.i++);
	}
	return (split(&ex));
}

int	ft_null(char *s)
{
	char	*s_q;
	char	*d_q;

	d_q = "\"\"";
	s_q = "\'\'";
	if (!ft_strcmp(s, s_q) || !ft_strcmp(s, d_q))
		return (1);
	return (0);
}

void ft_expand(t_token *tokens, int i, t_listenv *head)
{
	char **expanded;

	while (tokens)
	{
		if (tokens->value
			&& tokens->value[0] && !ft_null(tokens->value[0]))
		{
			expanded = expand_string(tokens->value[0], head, tokens->type);
			if (tokens->value)
			{
				i = 0;
				while (tokens->value[i])
				{
					free(tokens->value[i]);
					i++;
				}
				i = 0;
				free(tokens->value);
			}
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
