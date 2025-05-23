/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inte_export_tow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:46 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 14:33:26 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*build_variable_name(t_data *data,
	char *splt_egal, char **splt_plus)
{
	if (ft_strchr(data->args[1], '+'))
		return (ft_strjoin(splt_plus[0], "="));
	else if (tchking_egal(data->args[1]))
		return (ft_strjoin(splt_egal, "="));
	return (NULL);
}

static t_listenv	*search_variable(t_listenv *head,
	char *juny, int *found_flag)
{
	t_listenv	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->constvrble, juny))
		{
			*found_flag = 1;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static void	insert_or_update_variable(t_listenv **head,
	t_listenv *found, t_exptow *datatow)
{
	if (datatow->found_flag == 0)
	{
		ft_lstadd_back_ex(head, ft_lstnew_env(datatow->juny, datatow->pats));
	}
	else if (datatow->found_flag == 1 && found)
	{
		free(found->pat);
		found->pat = datatow->pats;
	}
	else
	{
		free(datatow->pats);
	}
}

void	ft_egal_pacslash(t_data *data,
	char *splt_egal, char **splt_plus, t_listenv *head)
{
	char		*juny;
	char		*pats;
	int			flags;
	t_listenv	*findd;

	pats = ft_strdup("");
	flags = 0;
	if (!pats)
		return ;
	juny = build_variable_name(data, splt_egal, splt_plus);
	if (!juny)
	{
		free(pats);
		return ;
	}
	findd = search_variable(head, juny, &flags);
	insert_or_update_variable(&head, findd, &(t_exptow){juny, pats, flags});
	free(juny);
}

void	pluss_egal_pacslash(t_data *data, int x, t_listenv **head, char *segal)
{
	t_listenv	*findd;
	char		*name;
	char		*value;

	extract_name_and_value(data->args[x], &name, &value);
	if (!name || !value)
	{
		free(name);
		free(value);
		return ;
	}
	findd = find_variable(*head, name);
	if (!findd)
	{
		ft_lstadd_back_ex(head, ft_lstnew_env(name, value));
		free(name);
		free(value);
	}
	else
	{
		free(findd->pat);
		findd->pat = ft_strdup(segal);
		free(value);
		free(name);
	}
}
