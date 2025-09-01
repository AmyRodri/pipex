/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/01 20:10:38 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Error");
	exit(1);
}

int	exec_first(int *file, int fd[2], t_cmd *cmd, char **envp)
{
	dup2(file[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	exec_mid(int *file, int fd[2], t_cmd *cmd, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	exec_final(int *file, int fd[2], t_cmd *cmd, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(file[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	exec_all(int *file, int (**pipes)[2], char **args, char **envp)
{
	pid_t	pid[3];
	int		status;
	int		ncmds;
	int		i;

	ncmds = 0;
	while (args[ncmds])
		ncmds++;
	ncmds -= 3;
	i = 0;
	while (i < ncmds)
	{
		if (i == 0)
		{
			pid[0] = fork();
			if (pid[0] < 0)
				return (perror("Fork"), 1);
			if (pid[0] == 0)
				exec_first(file, *pipes[0], parse_cmd(args[2], envp), envp);
		}
		else if (i == ncmds - 1)
		{
			pid[1] = fork();
			if (pid[1] < 0)
				return (perror("Fork"), 1);
			if (pid[1] == 0)
				exec_final(file, *pipes[i - 1], parse_cmd(args[3], envp), envp);
		}
		else
		{			
			pid[2] = fork();
			if (pid[1] < 0)
				return (perror("Fork"), 1);
			if (pid[1] == 0)
				exec_mid(file, *pipes[i - 1], parse_cmd(args[3], envp), envp);
		}
		i++;
	}
	closer_pipes(pipes, 2);
	closer_files(file, 2);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if ((status & 0xFF) == 0)
		return (status >> 8);
	return (0);
}
