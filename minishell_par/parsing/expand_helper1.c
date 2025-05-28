/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:32:53 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/28 11:11:33 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	extract_var(t_expand *ex, char *str)
{
	int	start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

char	*ft_getenv(t_expand *ex, t_token *tokens, t_listenv *head, t_tg *data)
{
	char	*new_varname;
	char	*env_name;

	env_name = NULL;
	new_varname = ft_strjoin(ex->var_name, "=");
	while (head)
	{
		if (ft_strcmp(new_varname, head->constvrble) == 0)
		{
			env_name = head->pat;
			break ;
		}
		head = head->next;
	}
	ft_ambigous(env_name, ex, data, tokens);
	return (free(new_varname), env_name);
}

void	handle_odd_dollars(t_expand *ex, t_token *tokens,
							t_listenv *head, t_tg *data)
{
	char	*val;
	char	*new_res;

	if (data->type != F_HERDOC && ft_isdigit(tokens->value[0][ex->i]))
		handle_num(ex, tokens);
	else if (tokens->value[0][ex->i] == '?')
		handle_status(ex, last_status( 22, 3));
	else if (data->type != F_HERDOC && (ft_isalnum(tokens->value[0][ex->i])
		|| tokens->value[0][ex->i] == '_'
		|| tokens->value[0][ex->i] == '?'))
	{
		extract_var(ex, tokens->value[0]);
		val = ft_getenv(ex, tokens, head, data);
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
	else
		append_char(ex, '$');
}

void	process_dollar(t_expand *ex, t_token *tokens,
						t_listenv *head, t_tg *data)
{
	ex->dollar_count = 0;
	while (tokens->value[0][ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars(ex, tokens, head, data);
}

void	handle_single_quote(t_expand *ex, t_token *tokens)
{
	ex->i++;
	while (tokens->value[0][ex->i] && tokens->value[0][ex->i] != '\'')
	{
		append_char(ex, tokens->value[0][ex->i]);
		ex->i++;
	}
	if (tokens->value[0][ex->i] == '\'')
		ex->i++;
}
