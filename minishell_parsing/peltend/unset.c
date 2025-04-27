/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:16 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/20 16:52:59 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_del(void *ptr)
{
    free(ptr);
}
char    *ft_strdup_unset(char *s)
{
	char	*str;
	int		len;
	int		i;
	
	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		if(s[i] == '=')
		  break;
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
// int main(int ac , char **av , char **env)
// {
void ft_unset(t_data *data,t_listenv **head)
{
	// t_listenv *head = NULL;
	
	// t_listenv *tmpe = head;
	// char *input = readline("Enter command: ");
	// char **str = ft_split(input , ' ');
	int i =1;
	// int i = 0;
	t_listenv *curr;
	t_listenv *prev;
	t_listenv *tmp;
	int flags = 0;
char *sss;
	while (data->args[i] != NULL)
	{
		curr = *head;
		prev = NULL;

		while (curr)
		{
			char *cope = ft_strdup_unset(curr->constvrble);
			// printf("%s",cope);
		
			
			if (!ft_strcmp(data->args[i],cope))
			{
				tmp = curr->next;
				if (prev != NULL)
					prev->next = tmp;
				else
					head = &tmp;
				ft_lstdelone(curr, my_del);
				curr = tmp;
				flags = 1;
			
			sss = cope;
			
			}
			else
			{
				// printf("%s%s\n", curr->constvrble, curr->pat);
				prev = curr;
				curr = curr->next;
			}
		}
		i++;
	if(flags == 0)
	{
		printf("unset: `%s': not a valid identifier\n",sss);
	}
	}
}