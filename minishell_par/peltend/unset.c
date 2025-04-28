/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:16 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/28 14:55:03 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_del(void *ptr)
{
    free(ptr);
}
char *ft_strdup_unset(char *s)
{
    char *str;
    int len;
    int i;
    
    i = 0;
    if (!s)
        return (NULL);
    len = ft_strlen(s);
    str = (char *)malloc((len + 1) * sizeof(char));
    if (!str)
        return (NULL);
    while (i < len && s[i] != '=')
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}
int ft_tchk_value(char *data)
{
    int i = 0;

    if (data[i] == '\0') 
        return 1;
    if (!ft_isalpha(data[i]) && data[i] != '_')  
        return 1;

    i++;
    while (data[i] != '\0')
    {
        if (!ft_isalnum(data[i]) && data[i] != '_') 
            return 1;
        i++;
    }
    return 0; 
}

void ft_unset(t_data *data,t_listenv **head)
{
	int i =1;

	t_listenv *curr;
	t_listenv *prev;
	t_listenv *tmp;
	int flags = 0;
char *sss = NULL;
	while (data->args[i] != NULL)
	{
			 if (ft_tchk_value(data->args[i]))  
        {
            printf("unset: `%s': not a valid identifier\n", data->args[i]);
            i++;
            continue;
        }
		curr = *head;
		prev = NULL;
		while (curr)
		{
			char *cope = ft_strdup_unset(curr->constvrble);
			if (!ft_strcmp(data->args[i],cope))
			{
				tmp = curr->next;
				if (prev != NULL)
					prev->next = tmp;
				else
					*head = tmp;
				ft_lstdelone(curr, my_del);
				curr = tmp;
				flags = 1;
			sss = cope;
			}
			else
			{

				prev = curr;
				curr = curr->next;
			}
			   if (cope)
                free(cope);
		}
		i++;
	flags = 0;
	}
	
}
