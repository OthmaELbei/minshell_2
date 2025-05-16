/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:18:45 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/15 16:02:17 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_listenv *tcchk_untel_egall(char *data,t_listenv *head)
{
	while(head)
	{
		if(!ft_strcmp(data,head->constvrble))
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}

int tcchk_untel_egll(char *data, t_listenv *head)
{
	while (head)
	{
		if (strcmp(data, head->constvrble) == 0)
		{
			return 1;
		}
		head = head->next;
	}
	return 0;
}

int ft_tchck_argmo_exat(char *data)
{
	int i = 0;
   if (!data || !(ft_isalpha(data[0]) || data[0] == '_' ))
		return 0;

	while (data[i] && data[i] != '=' && !(data[i] == '+' && data[i+1] == '=') )
	{
		if(  data[i] == ' ' )
		{
			return 0;
		}
		if (!(ft_isalnum(data[i]) || data[i] == '_') )
			return 0;
		i++;
	}
	return 1;
}

void tchek_only_key(char *data,char **splt_egal , char **splt_plus,t_listenv **head)
{
	t_listenv *found =  NULL;
	
	if(tcchk_untel_egll(splt_egal[0],*head) ==  1)
		{
			found = tcchk_untel_egall(splt_egal[0], *head);
			free(found->constvrble);
			found->constvrble = ft_strjoin(splt_egal[0],"=");
		}
			else if(tcchk_untel_egll(splt_plus[0],*head) ==  1 && ft_strchr(data,'+'))
		{
			found = tcchk_untel_egall(splt_plus[0], *head);
			free(found->constvrble);
			found->constvrble = ft_strjoin(splt_plus[0],"=");

		}
	free_copy_listenv(found);
}

void free_copy_listenv(t_listenv *head)
{
	t_listenv *head_new;
	while (head)
	{
		head_new = head;
		head = head->next;
		free(head_new->constvrble);
		free(head_new->pat);
		// free(head_new);
	}
}