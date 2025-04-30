/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:32:53 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/30 11:42:13 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_even_dollars(t_expand *ex)
{
	int num;
	char *dollars;
	char *new_res;

	num = ex->dollar_count / 2;
	dollars = malloc(num + 1);
	if (!dollars)
		return;
	ft_memset(dollars, '$', num);
	dollars[num] = '\0';
	new_res = ft_strjoin(ex->res, dollars);
	free(ex->res);
	free(dollars);
	ex->res = new_res;
}

void extract_var(t_expand *ex, char *str)
{
	int start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}


char	*ft_getenv(t_expand *ex, char *var_name, t_listenv *head, t_keyword type)
{
	char	*new_varname;
	char	*env_name;
	t_data	data;
	
	data.ambigous = 0;
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
	if (type >= FREAD_IN && type <= F_APPEND)
	{
		if (type != F_HERDOC && (env_name == NULL || word_count(env_name , ' ') > 1) && ex->flag == 0)
		{
			data.ambigous = 1;
			//printf("ambiguous redirect\n");
		}
	}
//	data.ambigous = 0; I don't Know if I should add this line --> icjeck i don't need it
	printf("ambigous: %d\n", data.ambigous);
	free(new_varname);
	return (env_name);
}


void handle_odd_dollars(t_expand *ex, char *str, t_listenv *head, t_keyword type)
{
	char *val;
	char *new_res;
	
	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		extract_var(ex, str);
		val = ft_getenv(ex, ex->var_name, head, type); // if I remove the export should check if THERE is NO EXPORT TO PREVENT THE SEGV
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}

void process_dollar(t_expand *ex, char *str, t_listenv *head, t_keyword type)
{
	// if (type == F_HERDOC) F_HERDOC
	// 	return ;
	ex->dollar_count = 0;
	while (str[ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars(ex, str, head, type);
	else
		handle_even_dollars(ex);
}

void handle_single_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '\'')
	{
		append_char(ex, str[ex->i]);
		ex->i++;
	}
	if (str[ex->i] == '\'')
		ex->i++;
	// ex->flag = 1;
}