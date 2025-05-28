/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_expand_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/27 23:18:14 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	append_char_herdoc(t_expand *ex, char c)
{
	char	*new_res;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}

void	extract_var_herdoc(t_expand *ex, char *str)
{
	int	start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_')
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

char	*ft_getenv_herdoc(char *var_name, t_listenv *head)
{
	char	*new_varname;
	char	*env_name;

	env_name = NULL;
	new_varname = ft_strjoin(var_name, "=");
	while (head)
	{
		if (ft_strcmp(new_varname, head->constvrble) == 0)
		{
			env_name = head->pat;
			break ;
		}
		head = head->next;
	}
	return (free(new_varname), env_name);
}

void	handle_odd_dollars_herdoc(t_expand *ex, char *str,
							int *flag, t_listenv *head)
{
	char	*val;
	char	*new_res;

	*flag = 0;
	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_')
	{
		extract_var_herdoc(ex, str);
		val = ft_getenv_herdoc(ex->var_name, head);
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}
