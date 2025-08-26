/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:59:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 12:01:08 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*parse_cmd(char *arg)
{
	t_cmd	*cmd;
	char	**splited;
	char	*path;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	splited = ft_split(arg, ' ');
	if (!splited || !splited[0])
		return (NULL);
	path = ft_strjoin("/bin/", splited[0]);
	cmd->path = path;
	cmd->argv = splited;
	return (cmd);
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Erro ao executar o comando");
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
