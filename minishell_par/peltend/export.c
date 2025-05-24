/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:17 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/23 15:35:15 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	only_key(char *data, char **splt_plus, t_listenv **head)
{
	char	*strnig;
	char	*packslach;

	strnig = ft_strjoin(data, "=");
	if (!strnig)
		return ;
	if (tcchk_untel_egll(splt_plus[0], *head) == 1)
	{
		data = splt_plus[0];
		// ft_free_ex(splt_plus);
		free(strnig);
		return ;
	}
	if (!tcchk_untel_egall(data, *head)
		&& !(tcchk_untel_egll(strnig, *head) == 1))
	{
		free(strnig);
		packslach = ft_strdup("\0");
		if (!packslach)
			return ;
		ft_lstadd_back_ex(head, ft_lstnew_env(data, packslach));
		free(packslach);
	}
	else
		free(strnig);
}

void	swap_sort_export(char *first_cont,
	char	*first_part, int *swap, t_listenv *timp)
{
	first_cont = timp->constvrble;
	first_part = timp->pat;
	timp->constvrble = timp->next->constvrble;
	timp->pat = timp->next->pat;
	timp->next->constvrble = first_cont;
	timp->next->pat = first_part;
	(*swap) = 1;
}

t_listenv	*sort_export(t_listenv *head)
{
	t_listenv		*timp;
	char			*first_cont;
	char			*first_part;
	int				swap;

	first_cont = NULL;
	first_part = NULL;
	swap = 1;
	timp = NULL;
	while (swap)
	{
		swap = 0;
		timp = head;
		while (timp && timp->next)
		{
			if (ft_strcmp(timp->constvrble, timp->next->constvrble) > 0)
				swap_sort_export(first_cont, first_part, &swap, timp);
			timp = timp->next;
		}
	}
	return (head);
}

void	print_export(char *consdt, char *pats_cotch)
{
	if (tchking_egal(consdt))
		printf("declare -x %s\"%s\"\n", consdt, pats_cotch);
	else
		printf("declare -x %s%s\n", consdt, pats_cotch);
}

int	ft_export(t_listenv *head, t_data *data)
{
	t_listenv	*sort_head;
	t_listenv	*copy;
	char		*consdt;
	char		*pats_cotch;

	copy = copy_listenv(head);
	if (!copy)
		return (0);
	sort_head = sort_export(copy);
	function_call(&head, data);
	while (sort_head)
	{
		consdt = ft_tchk_cotachen(sort_head->constvrble);
		pats_cotch = ft_tchk_cotachen(sort_head->pat);
		if (!ft_strcmp(data->args[0], "export") && data->args[1] == NULL)
			print_export(consdt, pats_cotch);
		free(consdt);
		free(pats_cotch);
		sort_head = sort_head->next;
	}
	free_copy_listenv(copy);
	return (0);
}
