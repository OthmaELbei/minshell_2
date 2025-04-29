/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:53:17 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/29 09:57:36 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_egal_pacslash(t_data *data, char **splt_egal, char **splt_plus, t_listenv *joune, t_listenv *head)
{
    char *juny;
    int x = 1;
    int flags = 0;
    char *pats = "";

    if (ft_strchr(data->args[x], '+'))
        juny = ft_strjoin(splt_plus[0], "=");
    else if (tchking_egal(data->args[x]))
        juny = ft_strjoin(splt_egal[0], "=");
    joune = head;
    t_listenv *findd = NULL;
    while (joune)
    {
        if (!ft_strcmp(joune->constvrble, juny))
        {
            flags = 1;
            findd = joune;
            break;
        }
        joune = joune->next;
    }
    if (flags == 0)
        ft_lstadd_back_ex(&head, ft_lstnew_env(juny, pats));
    else if (flags == 1 && findd)
        findd->pat = ft_strdup("\"\"");
}

void extract_name_and_value(char *arg, char **name, char **value)
{
    int i;
	int value_len;
	int name_len;
	
	name_len = 0;
	value_len = 0;
	i = 0;
    while (arg[i] != '=')
    {
        if (arg[i] != '+')
            name_len++;
        i++;
    }
    *name = malloc(name_len + 2); 
    int name_idx = 0, j = 0;
    while (arg[j] != '=')
    {
        if (arg[j] != '+')
            (*name)[name_idx++] = arg[j];
        j++;
    }
    (*name)[name_idx++] = '=';
    (*name)[name_idx] = '\0';
    value_len = strlen(arg + i + 1);
    *value = malloc(value_len + 1);
    strcpy(*value, arg + i + 1);
}

t_listenv *find_variable(t_listenv *head, char *name)
{
    while (head)
    {
        if (!ft_strcmp(head->constvrble, name))
            return head;
        head = head->next;
    }
    return NULL;
}
int find_varble(t_listenv *head, char *name)
{
    while (head)
    {
        if (!ft_strcmp(head->constvrble, name))
            return 1;
        head = head->next;
    }
    return 0;
}

void pluss_egal(t_data *data, int x, t_listenv *head, char **splt_egal)
{
    char *name;
    char *value;
    t_listenv *findd;

    extract_name_and_value(data->args[x], &name, &value);
    findd = find_variable(head, name);
    if (!findd)
        ft_lstadd_back_ex(&head, ft_lstnew_env(name, value));
    else
    {
        if (findd->pat)
        {
            char *new_pat = ft_strjoin(findd->pat, splt_egal[1]);
            free(findd->pat);
            findd->pat = new_pat;
        }
        else
            findd->pat = ft_strdup(splt_egal[1]);
    }
    free(name);
    free(value);
}


void pluss_egal_pacslash(t_data *data, int x, t_listenv **head, char **splt_egal)
{
    char *name;
    char *value;
    t_listenv *findd;

    extract_name_and_value(data->args[x], &name, &value);
    findd = find_variable(*head, name);

    if (!findd)
    {
        printf("Adding new variable\n");
        ft_lstadd_back_ex(head, ft_lstnew_env(name, value));
    }
    else
    {
        printf("Updating existing variable\n");
        free(findd->pat);
        findd->pat = strdup(splt_egal[1]);
    }

    free(name);
    free(value);
}
void function_call(t_listenv **head, t_data *data)
{
	
	     t_listenv *joune = *head;
		  int x = 1;
		   while (data->args[x])
    {
        int t = 0;
        char **splt_egal = ft_split(data->args[x], '=');
        char **splt_plus = ft_split(data->args[x], '+');

        if (thcking_pluss(data->args[x]) || tchking_egal(data->args[x]))
        {
            while (data->args[x][t] != '\0')
            {
                if (data->args[x][t] == '=' && data->args[x][t + 1] == '\0')
                {
                    ft_egal_pacslash(data, splt_egal, splt_plus, joune, *head);
                }
                else if (t > 0 &&  data->args[x][t - 1] == '+' && data->args[x][t] == '=' && data->args[x][t + 1] != '\0')
                {
                    pluss_egal(data, x, *head,splt_egal);
                }
                else if (t > 0 && data->args[x][t - 1] != '+' && data->args[x][t] == '=' && data->args[x][t + 1] != '\0')
                {
                    pluss_egal_pacslash(data, x, head,splt_egal);
                }
				
                t++;
            }
        }else 
		{  if(!find_varble( *head,data->args[x]))
			   ft_lstadd_back_ex(head, ft_lstnew_env(data->args[x],"\0"));
		}

        x++;
    }
}

void ft_export(t_listenv **head, t_data *data)
{
    int d = 0;
    int x = 0;
    // t_listenv *joune = *head;
    char *stralfa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
    // int x = 1;

   
 	function_call(head, data);
    if (!ft_strcmp(data->args[0], "export"))
    {
        while (stralfa[d])
        {
            t_listenv *tmp = *head;
            while (tmp)
            {
                char *strr = tmp->constvrble;
                if (stralfa[d] == strr[0])
                {
                    char *consdt = ft_tchk_cotachen(tmp->constvrble);
                    char *pats_cotch = ft_tchk_cotachen(tmp->pat);
					if(tchking_egal(consdt))
                    printf("%s\"%s\"\n", consdt, pats_cotch);
					else
					 printf("%s%s\n", consdt, pats_cotch);
                    free(consdt);
                    free(pats_cotch);
                }
				x++;
                tmp = tmp->next;
            }
            d++;
        }
    }
}
