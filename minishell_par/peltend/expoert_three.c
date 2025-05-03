/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoert_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:41:54 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/03 11:42:22 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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