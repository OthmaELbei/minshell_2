/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:37:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 14:32:36 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_arg_nam(char *arg, char **name)
{
	int	j;
	int	name_idx;

	j = 0;
	name_idx = 0;
	while (arg[j] != '=')
	{
		if (arg[j] != '+')
			(*name)[name_idx++] = arg[j];
		j++;
	}
	(*name)[name_idx++] = '=';
	(*name)[name_idx] = '\0';
}

int	ft_strlen_name(int *i, char *arg)
{
	int	name_len;

	name_len = 0;
	while (arg[*i] != '=')
	{
		if (arg[(*i)] != '+')
			name_len++;
		(*i)++;
	}
	if (!arg[*i])
		return (0);
	return (name_len);
}

void	extract_name_and_value(char *arg, char **name, char **value)
{
	int	i;
	int	value_len;
	int	name_len;

	*name = NULL;
	*value = NULL;
	name_len = 0;
	value_len = 0;
	i = 0;
	name_len = ft_strlen_name(&i, arg);
	*name = malloc(name_len + 2);
	if (!name)
		return ;
	copy_arg_nam(arg, name);
	value_len = ft_strlen(arg + i + 1);
	*value = malloc(value_len + 1);
	if (!*value)
	{
		free(*name);
		*name = NULL;
		return ;
	}
	ft_strcpy(*value, (arg + i + 1));
}

void	pluss_egal(t_data *data, int x, t_listenv *head, char *segal)
{
	char		*name;
	char		*value;
	t_listenv	*findd;
	char		*new_pat;

	extract_name_and_value(data->args[x], &name, &value);
	findd = find_variable(head, name);
	if (!findd)
		ft_lstadd_back_ex(&head, ft_lstnew_env(name, value));
	else
	{
		if (findd->pat)
		{
			new_pat = ft_strjoin(findd->pat, segal);
			free(findd->pat);
			findd->pat = ft_strdup(new_pat);
			free(new_pat);
		}
		else
			findd->pat = ft_strdup(segal);
	}
	free(name);
	free(value);
}

void	separe_egal_pluss(t_data *data, t_expcall *call, t_listenv **head)
{
	t_listenv	*joune;
	int			t;

	t = 0;
	joune = *head;
	while (data->args[call->x][t] != '\0')
	{
		t++;
		if (data->args[call->x][t] == '=')
			break ;
	}
	if (data->args[call->x][t] == '=' && data->args[call->x][t + 1] == '\0')
		ft_egal_pacslash(data, call->splt_egal, call->splt_plus,*head);
	else if (t > 0 && data->args[call->x][t - 1] == '+'
		&& data->args[call->x][t] == '=' && data->args[call->x][t + 1] != '\0')
		pluss_egal(data, call->x, *head, call->segal);
	else if (t > 0 && data->args[call->x][t - 1] != '+'
		&& data->args[call->x][t] == '=' && data->args[call->x][t + 1] != '\0')
		pluss_egal_pacslash(data, call->x, head, call->segal);
}
