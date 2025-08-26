/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/25 21:45:09 by kamys            ###   ########.fr       */
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

int	main(int num, char **args, char **envp)
{
	int		file[2];
	int		fd[2];
	pid_t	pid[2];

	if (num != 5)
		return (1);
	file[0] = open(args[1], O_RDONLY);
	file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file[0] < 0 || file[1] < 0)
		return (perror("erro ao abrir os arquivos"), 1);
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid[0] = fork();
	if (pid[0] == 0)
		exec_first(file, fd, parse_cmd(args[2]), envp);
	pid[1] = fork();
	if (pid[1] == 0)
		exec_segund(file, fd, parse_cmd(args[3]), envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
