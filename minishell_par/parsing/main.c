/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/25 15:30:25 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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

t_token *lexing(char *line, int *flag, t_listenv *head)
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
	ft_herdoc(&tokens, head);
	return (tokens);
}

// void ft_excution(t_data *data)
// {
// 	/*		printe cause leaks				*/
// 			// PRINT
// 			t_data *tmp = data;
// 			while (tmp)
// 			{

// 				printf("\n\n");
// 				printf("Command: %s\n", tmp->cmd ? tmp->cmd : "(no command)");

// 				// Print arguments
// 				printf("Arguments:");
// 				if (tmp->args)
// 				{
// 					// printf("tmp->arg[1]: %s\n", tmp->args[1]);
// 					for (int i = 0; tmp->args[i]; i++)
// 						printf(" |%s|", tmp->args[i]);
// 				}
// 				//Print files
// 				printf("\n");
// 				if (tmp->file)
// 				{
// 					while (tmp->file)
// 					{
// 						if (tmp->file->type != F_HERDOC)
// 						{
// 							printf("[fname: %s | ftype: %d | ambigous: %d]\n", 
// 									(tmp->file->name), tmp->file->type, tmp->file->_ambigous);
// 							free(tmp->file->name);
// 						}
// 						else
// 						{
// 							// if (tmp->file->fd < 0)
// 							// {
// 							// 	printf("error in fd \n");
// 							// 	return ;
// 							// }
// 							printf("[fd: %d | ftype: %d]\n",  (tmp->file->fd), tmp->file->type);
							
// 								char	buffer[1337];
// 								int		reads_size;
// 								if (tmp->file->fd < 0)
// 									printf("fd is failed\n");
								


// 								reads_size = read(tmp->file->fd, buffer, 1337);
// 								printf("reads_size: %d\n", reads_size);
								
// 								buffer[reads_size] = '\0';
								
// 								printf("buffer: %s\n", buffer);
// 								if (reads_size <= 0)
// 									printf("reads_size read nothing\n");
// 						}
						
// 						tmp->file = tmp->file->next;
// 					}
					
// 				}
// 				tmp = tmp->next;
// 			}
// }


void	helper_main(t_token *tokens, int *flag, t_listenv *head)
{
	t_data	*data;
	t_token *temp;
	int		st;

	// t_listenv *head = NULL;

	temp = NULL;
	if (*flag == 0)
	{
		data = parsing(&tokens, temp);

		// ft_excution(data);

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
		temp = tokens; // you can just send the tokens not `temp` cause if send tokens you send just by value not by referense so do it if you need more lines in this function
		ft_open_herdoc_until_error(temp, head);
		free_tokens(tokens);
	}
}

void	f()
{
	system("leaks minishell ");
}
void disable_echoctl(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void siginl_hendel(int sig)
{
	
	(void)sig;
	write(STDOUT_FILENO, "\n", 1); 
	// rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
	
}
int main(int ac, char **av, char **env)
{
	store_pwd(NULL, 1);
	(void)ac, (void)av;
	t_token		*tokens;
	t_listenv 	*head;
	t_v_main	variable;
	// atexit(f);
	signal(SIGINT, siginl_hendel);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();


	head = NULL;
	if (head == NULL)
		ft_env(env, &head);

	head->fdd = 0;

	tokens = NULL;
	while (1)
	{
		variable.flag = 0;
		variable.line = readline("Minishell: ");
		if(!variable.line)
		{
			printf("exit\n");
			// free(variable.line);
				// free_copy_listenv(head);
			exit(head->fdd);
		}
		if (variable.line == NULL)
			break;
		tokens = lexing(variable.line, &variable.flag, head);
		if (tokens != NULL)
			helper_main(tokens, &variable.flag, head);
		if (variable.line[0] != '\0')
			add_history(variable.line);
		free(variable.line);
	}
		// free(head->old_pwd);
		free_copy_listenv(head);
	return (0);
}




































































/* Problem
	the problem the leaks maybe 89% in free_data => when we call multiple file maybe we are not free the previous allocation of these files
	the test: < a < b < c > d

*/







































































































// void	lexing(char *line)
// {
// 	int		i;
// 	int		count_quote;
// 	t_token	*tokens;

// 	i = 0;
// 	count_quote = 0;
// 	if (check_quotes(line, i, count_quote))
// 		return (ft_putstr_fd("missing quotation\n", 2));

// 	tokens = tokenization(line, i);
// 	if (tokens == NULL)
// 		return ;
// 	// error(tokens);
// 	// ft_rename(tokens);
// 	// ft_expand(tokens);
// 	// ft_herdoc(tokens);

// 	t_token *temp;

// 	temp = tokens;

// 	// printf("@==> %s\n", temp->value[0]);

// 	while (temp)
// 	{
// 		int	i = 0;
// 		if (temp->value)
// 		{
// 			while (temp->value[i])
// 			{
// 					printf("\n | %s |\n", temp->value[i]);
// 					i++;
// 			}
// 		}
// 		temp = temp->next;
// 	}

// }



/*************************************/
//  handle this cas '' '' '' ''  
// add `command` as argument also, cause execve need it


/* problem
	syntax error ;;
*/

/*
there still a problem when i write '           ' => the problem is not print l espace
exept when somethig in single_quote like this => '        .'
so should fix this issue when i have a space in single quote should keep the space '      '
*/

/* 
	problem in herdoc "ok" => khaso irooj bi ok bla ""
	check this in your bash and compare it with real bash
*/

/* problem
<< ok |||| << d
check this in your bash and compare it with real bash
*/

/* problem
	close(fd) => if I close it fd in parsing the executer can't open it again will lose so be carefule and find a solution 
*/


/* problem
	in expand should handle numberes
*/

