/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:50:43 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/28 12:08:21 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *line, int i, int count_quote)
{
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			count_quote++;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				count_quote++;
			else
				break ;
			i++;
		}
		else
			i++;
	}
	if (count_quote % 2)
		return (1);
	return (0);
}

t_token	*lexing(char *line, int *flag, t_listenv *head)
{
	int		i;
	int		count_quote;
	t_token	*tokens;
	t_token	*current;

	i = 0;
	count_quote = 0;
	if (check_quotes(line, i, count_quote))
		return (ft_putstr_fd("missing quotation\n", 2), NULL);
	tokens = tokenization(line, i);
	if (tokens == NULL)
		return (NULL);
	tokens->fd = 0;
	current = NULL;
	if (error(tokens, current))
	{
		head->fdd = 258;
		*flag = 1;
		return (tokens);
	}
	ft_rename(tokens);
	ft_expand(tokens, i, head);
	if (ft_herdoc(&tokens, head) == -13)
		return (tokens->herdoc = -13, tokens);
	return (tokens);
}

int	helper_main(t_token *tokens, int *flag, t_listenv *head)
{
	t_data	*data;
	t_token	*temp;
	int		st;

	temp = NULL;
	if (*flag == 0)
	{
		data = parsing(&tokens, temp);
		st = ft_execoshen(data, head);
		head->fdd = st;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		dup2(STDERR_FILENO, STDIN_FILENO);
		
		free_data(data);
		free_tokens(tokens);
	}
	else
	{
		ft_rename(tokens);
		temp = tokens;
		if (ft_open_herdoc_until_error(temp, head) == -13)
			return (free_tokens(tokens), -13);
		free_tokens(tokens);
	}
	return (0);
}
