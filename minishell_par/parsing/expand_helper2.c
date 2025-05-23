/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:35:54 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/20 13:07:27 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	append_char(t_expand *ex, char c)
{
	char	*new_res;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}

void	ft_ambigous(char *env_name, t_expand *ex, t_tg *data, t_token *tokens)
{
	if (data->type >= FREAD_IN && data->type <= F_APPEND)
	{
		if (data->type != F_HERDOC
			&& (env_name == NULL || word_count(env_name, ' ') > 1))
		{
			if ((env_name == NULL && ex->flag == 0 && data->quote == 0)
				|| (ex->flag == 0 && word_count(env_name, ' ') > 1))
				tokens->_ambigous = ambigous;
		}
	}
}

void	handle_num(t_expand *ex, t_token *tokens)
{
	char	*new_res;

	ex->i++;
	extract_var(ex, tokens->value[0]);
	new_res = ft_strjoin(ex->res, ex->var_name);
	free(ex->res);
	free(ex->var_name);
	ex->res = new_res;
	// free(new_res); //============> hadi ka SEGV
}

void	handle_status(t_expand *ex, int status)
{
	char	*stat;
	char	*new_res;

	ex->i++;
	stat = ft_itoa(status);
	new_res = ft_strjoin(ex->res, stat);
	free(ex->res);
	free(stat);
	// free(new_res); //============> hadi ka SEGV ========> heap-use-after-free on address
	ex->res = new_res;
}
