/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/02 15:57:46 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Error");
	exit(1);
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

int	exec_all(int *file, int (*pipes)[2], char **args, char **envp)
{
	pid_t	pid;
	int		status;
	int		ncmds;
	int		i;

	ncmds = ft_strlen(args) - 3;
	i = 0;
	while (i < ncmds)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_pipes_fds(file, pipes, ncmds, i);
			closer_files(file, 2);
			exec_cmd(parse_cmd(args[2 + i], envp), envp);
			perror("exec failed");
			exit(1);
		}
		else if (pid < 0)
			perror("fork failed");
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < ncmds - 1)
			close(pipes[i][1]);
		i++;
	}
	closer_files(file, 2);
	i = 0;
	while (i < ncmds)
	{
		wait(&status);
		i++;
	}
	return (0);
}

