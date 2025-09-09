/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:50:46 by kamys             #+#    #+#             */
/*   Updated: 2025/09/09 19:54:16 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	free_exit(int (*pipes)[2], int ret)
{
	free(pipes);
	return (ret);
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
