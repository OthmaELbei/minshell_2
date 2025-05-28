/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/28 10:19:43 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	siginl_hendel(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	init_shell(char **env, t_listenv **head)
{
	store_pwd(NULL, 1);
	signal(SIGINT, siginl_hendel);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();
	if (*head == NULL)
	{
		printf("Hello\n");
		ft_env(env, head);
	}
	(*head)->fdd = 0;
}

void	mama_funtion(t_v_main variable, t_token *tokens, t_listenv *head)
{
	while (1)
	{
		variable.flag = 0;
		variable.line = readline("Minishell: ");
		if (!variable.line)
			(/*free(variable.line), free_copy_listenv(head),*/ exit(head->fdd));
		tokens = lexing(variable.line, &variable.flag, head);
		if (tokens == NULL || tokens->herdoc == -13)
		{
			(free_tokens(tokens), /*should free ft_env*/ free(variable.line));
			continue ;
		}
		if (tokens != NULL)
		{
			if (helper_main(tokens, &variable.flag, head) == -13)
			{
				free(variable.line);
				continue ;
			}
		}
		if (variable.line[0] != '\0')
			add_history(variable.line);
		free(variable.line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_token		*tokens;
	t_listenv	*head;
	t_v_main	variable;

	
	(void)ac;
	(void)av;
	ft_memset(&variable, 0, sizeof(t_v_main));
	tokens = NULL;
	head = NULL;	
	init_shell(env, &head);
	mama_funtion(variable, tokens, head);
	return (free_copy_listenv(head), 0);
}
