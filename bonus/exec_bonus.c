/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/03 10:36:43 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Error");
	exit(1);
}

static void	parent_exec(int (*pipes)[2], int n_cmds, int i, pid_t pid)
{
	if (pid < 0)
		perror("fork failed");
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < n_cmds - 1)
		close(pipes[i][1]);
}

int	exec_all(int *file, int (*pipes)[2], char **args, char **envp)
{
	pid_t	pid;
	int		n_cmds;
	int		i;

	n_cmds = ft_argslen(args) - 3;
	i = 0;
	while (i < n_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_pipes_fds(file, pipes, n_cmds, i);
			closer_files(file, 2);
			exec_cmd(parse_cmd(args[2 + i], envp), envp);
		}
		parent_exec(pipes, n_cmds, i, pid);
		i++;
	}
	wait_closer(file, n_cmds);
	return (0);
}
