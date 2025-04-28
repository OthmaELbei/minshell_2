/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:54:22 by oelbied           #+#    #+#             */
/*   Updated: 2025/04/20 08:39:49 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// t_listenv	*ft_lstnew(void *content)
// {
// 	t_listenv	*head;

// 	head = (t_listenv *)malloc((sizeof(t_listenv)));
// 	if (head == NULL)
// 		return (NULL);
// 	head -> constvrble = content;
// 	head -> next = NULL;
// 	return (head);
// }
// t_listenv	*ft_lstnew_pat(void *content)
// {
// 	t_listenv	*head;

// 	head = (t_listenv *)malloc((sizeof(t_listenv)));
// 	if (head == NULL)
// 		return (NULL);
// 	head -> pat = content;
// 	head -> next = NULL;
// 	return (head);
// }
t_listenv *ft_lstnew_env(char *content, char *path)
{
    t_listenv *new;

    new = (t_listenv *)malloc(sizeof(t_listenv));
    if (!new)
        return (NULL);
    new->constvrble = strdup(content); // نسخ المحتوى باستخدام strdup
    new->pat = strdup(path);          // نسخ المسار باستخدام strdup
    new->next = NULL;
    return (new);
}
