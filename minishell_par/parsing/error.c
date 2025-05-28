/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:50:45 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/27 23:26:56 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	t_err(t_token **current)
{
	(*current)->error = -1;
}

int	check( t_keyword ptype, t_keyword ctype, t_keyword ntype)
{
	if (ptype == WORD && ctype == WRITE_OUT && ntype == PIPE)
		return (1);
	return (0);
}

int	redierct_check(t_token *prev, t_token *current, t_token *next)
{
	if (!next)
		return (1);
	if (prev && check(prev->type, current->type, next->type))
		return (1);
	else if (current->type == HERDOC && next->type == WRITE_OUT)
		return (1);
	else if ((prev && prev->type == FWRITE_OUT)
		&& current->type == PIPE && next->type == WORD)
		return (1);
	else if (!(current->type >= WRITE_OUT && current->type <= APPEND))
	{
		if (!next && (next->type >= WRITE_OUT && next->type <= HERDOC))
			return (1);
	}
	else if ((!next || next->type != WORD) && next->type != WRITE_OUT)
	{
		if ((next->type >= READ_IN && next->type <= HERDOC))
			return (1);
	}
	else if (next->type == WORD && prev && is_pipe(prev->type))
		;
	else if (prev && (is_redirect(prev->type) || is_pipe(prev->type))
		&& next->type != WORD)
		return (1);
	return (0);
}

int	is_invalide(t_token *token, char **value)
{
	int	count;

	count = 0;
	count = ft_strlen(value[0]);
	if (token->type == PIPES)
		return (1);
	else if (count > 2)
		return (1);
	return (0);
}

int	error(t_token *tokens, t_token *current)
{
	t_token	*prev;
	t_token	*next;

	current = tokens;
	prev = NULL;
	if (is_pipe(current->type))
		return (ft_putstr_fd(ERROR, STDERR_FILENO), t_err(&current), 1);
	while (current)
	{
		next = current->next;
		if (is_pipe(current->type))
			if (pipe_check(prev, next) || is_invalide(current, current->value))
				return (ft_putstr_fd(ERROR, STDERR_FILENO), t_err(&current), 1);
		if (is_redirect(current->type))
			if (redierct_check(prev, current, next)
				|| is_invalide(current, current->value))
				return (ft_putstr_fd(ERROR, STDERR_FILENO), t_err(&current), 1);
		prev = current;
		current = next;
	}
	if (prev && (is_redirect(prev->type) || is_pipe(prev->type)))
		return (ft_putstr_fd(ERROR, STDERR_FILENO), t_err(&current), 1);
	return (0);
}
