/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inte_excoshen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:05:12 by oelbied           #+#    #+#             */
/*   Updated: 2025/05/28 12:19:45 by oelbied          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_freee(char **arrai)
{
	int	i;

	i = 0;
	if (!arrai)
		return ;
	while (arrai[i])
		free(arrai[i++]);
	free(arrai);
}

void	thcke_fd(t_data *data, int fd)
{
	if (fd == -1)
	{
		perror(data->file->name);
		exit(EXIT_FAILURE);
	}
}

void	ft_closse(t_redir *redir, int fd)
{
	if (redir->type == FWRITE_OUT
		|| redir->type == FREAD_IN || redir->type == F_APPEND)
	{
		thcke_fd(NULL, fd);
		close(fd);
	}
}

void	ft_tchek_herdok(t_redir **redir)
{
	dup2((*redir)->fd, STDIN_FILENO);
	close((*redir)->fd);
	(*redir)->fd = -1;
	// unlink((*redir)->name);
	// *redir = (*redir)->next;
}

void	ft_erorr(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
