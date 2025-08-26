/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 14:25:00 by amyrodri         ###   ########.fr       */
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
