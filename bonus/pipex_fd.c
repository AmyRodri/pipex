/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:50:46 by kamys             #+#    #+#             */
/*   Updated: 2025/09/02 19:51:40 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	closer_pipes(int (*pipes)[2], int len, int j)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i == j)
			continue ;
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	closer_files(int *files, int len)
{
	int	i;

	i = 0;
	while (i < len)
		close(files[i++]);
}

void	setup_pipes_fds(int *file, int (*pipes)[2], int ncmds, int i)
{
	int	j;

	if (i == 0)
	{
		dup2(file[0], STDIN_FILENO);
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	else if (i == ncmds - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(file[1], STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < ncmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

int	wait_closer(int *file, int n_cmds)
{
	int	i;
	int	status;

	closer_files(file, 2);
	i = 0;
	while (i < n_cmds)
	{
		wait(&status);
		i++;
	}
	return (status);
}