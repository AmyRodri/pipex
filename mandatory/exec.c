/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 16:58:29 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Error");
	exit(1);
}

int	exec_first(int *file, int *fd, t_cmd *cmd, char **envp)
{
	dup2(file[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	exec_segund(int *file, int *fd, t_cmd *cmd, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(file[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(cmd, envp);
	return (1);
}

int	exec_all(int *file, int *fd, char **args, char **envp)
{
	pid_t	pid[2];
	int		status;

	pid[0] = fork();
	if (pid[0] < 0)
		return (perror("Fork"), 1);
	if (pid[0] == 0)
		exec_first(file, fd, parse_cmd(args[2], envp), envp);
	pid[1] = fork();
	if (pid[1] < 0)
		return (perror("Fork"), 1);
	if (pid[1] == 0)
		exec_segund(file, fd, parse_cmd(args[3], envp), envp);
	closer(fd, 2);
	closer(file, 2);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if ((status & 0xFF) == 0)
		return (status >> 8);
	return (0);
}
