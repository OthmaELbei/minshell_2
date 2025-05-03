/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:37:24 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/03 11:42:08 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void separe_egal_pluss(t_data *data, int x,char **splt_egal,char **splt_plus,t_listenv **head)
{
	t_listenv *joune;
	int t;

	t = 0;
	joune = *head;
	while (data->args[x][t] != '\0')
    {
		if (data->args[x][t] == '=' && data->args[x][t + 1] == '\0')
            ft_egal_pacslash(data, splt_egal, splt_plus, joune, *head);
        else if (t > 0 &&  data->args[x][t - 1] == '+' && data->args[x][t] == '=' && data->args[x][t + 1] != '\0')
            pluss_egal(data, x, *head,splt_egal);
        else if (t > 0 && data->args[x][t - 1] != '+' && data->args[x][t] == '=' && data->args[x][t + 1] != '\0')
            pluss_egal_pacslash(data, x, head,splt_egal);
		t++;
	}
	
}