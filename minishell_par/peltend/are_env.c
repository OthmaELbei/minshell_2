/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:04:48 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/23 14:11:36 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_ar_env(t_listenv *head)
{
	t_listenv	*joune;
	char		**to_pt;
	int			p;
	int			d;

	p = 0;
	d = ft_lstsize(head);
	to_pt = (char **)malloc(sizeof(char *) * (d + 1));
	joune = head;
	while (joune)
	{
		char *conts = joune->constvrble;
		char *pats = joune->pat;
		char *opreter_joun = ft_strjoin(conts, pats);
		int lines = ft_strlen(opreter_joun) + 1;
		to_pt[p] = (char *)malloc(sizeof(char) * (lines));
		ft_strlcpy(to_pt[p], opreter_joun, lines);
		p++;
		joune = joune->next;
	}
	to_pt[p] = NULL;
	// free_copy_listenv(head);
	return to_pt;
}