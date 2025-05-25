/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:04:48 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/24 21:33:12 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	make_are_env(char **to_pt, t_listenv	*joune, int lines)
{
	char		*opreter_joun;
	char		*conts;
	char		*pats;
	int			p;

	p = 0;
	while (joune)
	{
		conts = joune->constvrble;
		pats = joune->pat;
		opreter_joun = ft_strjoin(conts, pats);
		free(conts);
		free(pats);
		lines = ft_strlen(opreter_joun) + 1;
		to_pt[p] = (char *)malloc(sizeof(char) * (lines));
		ft_strlcpy(to_pt[p], opreter_joun, lines);
		free(opreter_joun);
		p++;
		joune = joune->next;
	}
	to_pt[p] = NULL;
}

char	**ft_ar_env(t_listenv *head)
{
	t_listenv	*joune;
	char		**to_pt;
	int			d;
	int			lines;

	lines = 0;
	d = ft_lstsize(head);
	to_pt = (char **)malloc(sizeof(char *) * (d + 1));
	joune = head;
	make_are_env(to_pt, joune, lines);
	return (to_pt);
}
