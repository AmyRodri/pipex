/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:29:47 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/04 13:39:26 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_here_doc(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	setup_here_d(char **args, int file[2], int num)
{
	int	here_d[2];

	if (!check_here_d(args[1]))
	{
		file[0] = open(args[1], O_RDONLY);
		if (file[0] < 0)
			return (perror("Error infile"), 1);
		file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file[1] < 0)
			return (perror("Error outfile"), 1);
	}
	else
	{
		if (pipe(here_d) == -1)
			return (perror("Error pipe"), 1);
		write_here_doc(here_d[1], args[2]);
		close(here_d[1]);
		file[0] = here_d[0];
		file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file[1] < 0)
			return (perror("Error outfile"), 1);
	}
	return (0);
}

int	start_pipes(int (*pipes)[2], int num)
{
	int	i;

	i = 0;
	while (num - 4 > i)
	{
		if (pipe(pipes[i]) == -1)
			return (perror("Error pipe"), 1);
		i++;
	}
	return (0);
}
