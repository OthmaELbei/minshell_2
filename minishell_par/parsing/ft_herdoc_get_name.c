/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_get_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:22:55 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/20 13:23:22 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_word(int fd)
{
	char	*name;
	char	buffer;
	int		count;

	name = malloc(name_length + 1);
	if (!name)
		return (close(fd), printf("failed malloc\n"), NULL);
	count = 0;
	while (count < name_length)
	{
		if (read(fd, &buffer, 1) < 0)
		{
			close(fd);
			perror("read failed\n");
			return (NULL);
		}
		if (ft_isalnum(buffer))
			name[count++] = buffer;
	}
	name[name_length] = '\0';
	close(fd);
	return (name);
}

char	*generate_name(void)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (perror("failed to open /dev/random"), NULL);
	return (get_word(fd));
}

int	check_delimter(char *delimter)
{
	int	i;

	i = 0;
	while (delimter[i])
	{
		if (delimter[i] == '\'' || delimter[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
