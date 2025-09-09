/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/09 19:02:25 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(t_cmd *cmd, char **envp)
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

static void	here_d_cmds(char **args, int *n_cmds, int *start_cmds)
{
	if (!check_here_d(args[1]))
	{
		*start_cmds = 2;
		*n_cmds = ft_argslen(args) - 3;
	}
	else
	{
		*start_cmds = 3;
		*n_cmds = ft_argslen(args) - 4;
	}
}

static void	setup_pipes_fds(int *file, int (*pipes)[2], int ncmds, int i)
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

int	exec_all(int *file, int (*pipes)[2], char **args, char **envp)
{
	pid_t	pid;
	int		n_cmds;
	int		i;
	int		start_cmds;

	start_cmds = 0;
	n_cmds = 0;
	here_d_cmds(args, &n_cmds, &start_cmds);
	i = 0;
	while (i < n_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_pipes_fds(file, pipes, n_cmds, i);
			closer_files(file, 2);
			exec_cmd(parse_cmd(args[start_cmds + i], envp), envp);
		}
		parent_exec(pipes, n_cmds, i, pid);
		i++;
	}
	wait_closer(file, n_cmds);
	closer_pipes(pipes, n_cmds - 1, -1);
	closer_files(file, 2);
	return (0);
}
