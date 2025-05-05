/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:17 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/05 10:15:37 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void only_key(char *data,char **splt_plus,t_listenv **head)
{
	char *strnig = ft_strjoin(data,"=");
	if (tcchk_untel_egll(splt_plus[0],*head) ==  1)
		data = splt_plus[0];
	if (!tcchk_untel_egall(data, *head) && !(tcchk_untel_egll(strnig,*head) ==  1) )
		ft_lstadd_back_ex(head, ft_lstnew_env(data,"\0")); 
}

void function_call(t_listenv **head, t_data *data)
{
	char **splt_egal;
	char **splt_plus; 
	int x;

	x = 1;
	while (data->args[x])
    {
       	splt_egal = ft_split(data->args[x], '=');
	   	if(!splt_egal || !splt_plus)
	    	return;
       	splt_plus = ft_split(data->args[x], '+');
		if(!ft_tchck_argmo_exat(data->args[x]))
		{
			printf("export: '%s': not a valid identifier\n", data->args[x]);
			x++;
			continue;
		}
   	  	if (thcking_pluss(data->args[x]) || tchking_egal(data->args[x]))
        {
			tchek_only_key(data->args[x],splt_egal ,splt_plus,head);
			separe_egal_pluss(data,  x,splt_egal,splt_plus,head);
        }
		else 
			only_key(data->args[x],splt_plus,head);
        x++;
    }
}

t_listenv *copy_listenv(t_listenv *head)
{
	t_listenv *new_head = NULL;
	t_listenv *last = NULL;

	while (head)
	{
		t_listenv *new_node = malloc(sizeof(t_listenv));
		if (!new_node)
			return NULL;

		new_node->constvrble = strdup(head->constvrble);
		new_node->pat = strdup(head->pat);
		new_node->next = NULL;

		if (!new_head)
			new_head = new_node;
		else
			last->next = new_node;

		last = new_node;
		head = head->next;
	}
	return new_head;
}

t_listenv *sort_export(t_listenv *head)
{
	t_listenv *timp = NULL;
	char *first_cont;
	char *first_part;

	int swap = 1 ;
	while(swap){
		swap =0;
	timp = head;
		
	while(timp && timp->next)
	{
		if(ft_strcmp(timp->constvrble,timp->next->constvrble) > 0)
		{
		   first_cont = timp->constvrble;
		   first_part = timp->pat;
		   timp->constvrble = timp->next->constvrble;
		   timp->pat= timp->next->pat;
		   timp->next->constvrble = first_cont;
		   timp->next->pat = first_part ;
		   swap = 1;
		}
		timp = timp->next;
	}	
	}
	return head;	
}
void ft_export(t_listenv *head, t_data *data)
{
	t_listenv *copy = copy_listenv(head);
    t_listenv *sort_head = sort_export(copy );

 	function_call(&head, data);
            while (sort_head)
            {
             char *consdt = ft_tchk_cotachen(sort_head->constvrble);
            char *pats_cotch = ft_tchk_cotachen(sort_head->pat);
					 if (!ft_strcmp(data->args[0], "export") && data->args[1] == NULL)
					 {
						if(tchking_egal(consdt))
                   		 printf("%s\"%s\"\n", consdt, pats_cotch);
						else
						 printf("%s%s\n", consdt, pats_cotch);
					 }
                    free(consdt);
                    free(pats_cotch);
                    sort_head = sort_head->next;
              }
			free_copy_listenv(copy);
}
