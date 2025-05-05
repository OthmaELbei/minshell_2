/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:04:48 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/05 10:08:30 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **ft_ar_env(t_listenv *head)
{
	int p = 0;
	int d = ft_lstsize(head);
	char	**to_pt = (char **)malloc(sizeof(char *) * (d + 1));
	t_listenv *joune = head;
		
			while(joune)
			{
				char *conts = joune->constvrble;
				char *pats = joune->pat;
				char *opreter_joun = ft_strjoin(conts,pats);
				int lines = ft_strlen(opreter_joun) + 1;
				to_pt[p] = (char *)malloc(sizeof(char) * (lines));
				ft_strlcpy(to_pt[p], opreter_joun, lines);
				p++;
				joune = joune->next;
			}
		to_pt[p] = NULL;
free_copy_listenv(head);
	return to_pt;
}