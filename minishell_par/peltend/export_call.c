/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:12:37 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/22 14:31:49 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_arguments(t_data *data, int x, char **splt_plus)
{
	if (!splt_plus)
		return (0);
	if (!ft_tchck_argmo_exat(data->args[x]))
	{
		printf("export: '%s': not a valid identifier\n", data->args[x]);
		return (0);
	}
	return (1);
}

static void	extract_arguments(t_data *data, int x,
	char **splt_egal, char **segal)
{
	int	d;

	if (ft_strchr(data->args[x], '='))
	{
		d = 0;
		while (data->args[x][d] != '=')
			d++;
		*splt_egal = ft_substr(data->args[x], 0, d);
		if (*splt_egal)
		{
			*segal = ft_substr(data->args[x], d + 1,
					ft_strlen(data->args[x]) - d - 1);
			if (!*segal)
				free(*splt_egal);
		}
	}
}

static void	execute_operation(t_listenv **head, t_data *data, t_expcall *call)
{
	if (thcking_pluss(data->args[call->x]) || tchking_egal(data->args[call->x]))
	{
		tchek_only_key(data->args[call->x], call, head);
		separe_egal_pluss(data, call, head);
	}
	else
	{
		only_key(data->args[call->x], call->splt_plus, head);
	}
}

static void	handle_single_argument(t_listenv **head, t_data *data, int x)
{
	char	*splt_egal;
	char	**splt_plus;
	char	*segal;

	splt_egal = NULL;
	splt_plus = NULL;
	segal = NULL;
	extract_arguments(data, x, &splt_egal, &segal);
	splt_plus = ft_split(data->args[x], '+');
	if (!process_arguments(data, x, splt_plus))
	{
		cleanup_memory(splt_egal, splt_plus, segal);
		return ;
	}
	execute_operation(head, data, &(t_expcall){x, splt_egal, splt_plus, segal});
	cleanup_memory(splt_egal, splt_plus, segal);
}

void	function_call(t_listenv **head, t_data *data)
{
	int	x;

	x = 1;
	while (data->args[x])
	{
		handle_single_argument(head, data, x);
		x++;
	}
}
