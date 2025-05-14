/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:24:15 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/12 13:16:44 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_tchk_egal(char *str)

{
		int j;
		j = 0;
		if(!str)
		return 0;
		while (str[j] != '\0')
		{
			if(str[j] == '=')
			break;
			j++;
		}
		return j;
}
int env_copy(char *env, char *str)
{
	int k =0;
	int	j = 0;
	if(!env || !str)
		return 0;
		while (env[j] != '\0')
		{
			str[j] = env[j];
			k++;
			if(env[j] == '=')
				break;
			j++;
		}
		str[k] = '\0';
	return j;
}

void ft_env(char **env, t_listenv **head)
{
	int i = 0;
	int j = 0;
	    int name_len;
	char *str;
	char *pat;
if(!env ||!env[0])
{
		t_listenv *node_env;
	node_env = ft_lstnew_env("PATH=","/bin:/usr/bin");
	ft_lstadd_back_ex(head,node_env);
	node_env = ft_lstnew_env("PWD=","/mnt/homes/oelbied/Desktop/minshell_2/minishell_par");
	ft_lstadd_back_ex(head,node_env);
	node_env = ft_lstnew_env("SHLVL=","1");
	ft_lstadd_back_ex(head,node_env);
	node_env = ft_lstnew_env("_=","/usr/bin/env");
	ft_lstadd_back_ex(head,node_env);
	
}
	while(env[i])
	{
		  name_len = ft_tchk_egal(env[i]);
        if (name_len == -1)
        {
            i++;
            continue; 
        }
		str = (char *)malloc((name_len + 2) * sizeof(char));
		if(!str)
		return ;
	
	    j = env_copy(env[i], str);
		pat = ft_strdup(env[i] + j + 1);
		if(!pat)
			return (free(str));
		t_listenv *node_env = ft_lstnew_env(str,pat);
		if(!node_env)
		{
			free(str);
			free(pat);
			return;
		}
		ft_lstadd_back_ex(head,node_env);
		i++;
		free(str);
		free(pat);
	}

}
