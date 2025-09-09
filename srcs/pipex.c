/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/09 19:20:38 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	(*pipes_setup(int num, char **args, int *file, int *n_cmds))[2]
{
	int	(*pipes)[2];

	if (check_args(args, num, file))
		return (NULL);
	if (!check_here_d(args[1]))
		*n_cmds = num - 3;
	else
		*n_cmds = num - 4;
	pipes = malloc((*n_cmds - 1) * sizeof(*pipes));
	if (!pipes)
		return (NULL);
	if (start_pipes(pipes, *n_cmds))
	{
		free(pipes);
		return (NULL);
	}
	return (pipes);
}

int	main(int num, char **args, char **envp)
{
	int	(*pipes)[2];
	int	file[2];
	int	n_cmds;

	pipes = pipes_setup(num, args, file, &n_cmds);
	if (!pipes)
		return (1);
	if (exec_all(file, pipes, args, envp))
		return (free_exit(pipes, 1));
	free(pipes);
	return (0);
}
