/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:24:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/02 14:59:44 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->argv, envp);
	perror("Error");
	exit(1);
}

int	exec_all(int *file, int (*pipes)[2], char **args, char **envp)
{
	pid_t	pid;
	int		status;
	int		ncmds;
	int		i;
	int		j;

	ncmds = 0;
	while (args[ncmds])
		ncmds++;
	ncmds -= 3;
	i = 0;
	while (i < ncmds)
	{
		pid = fork();
		if (pid == 0)
		{
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
			closer_files(file, 2);
			exec_cmd(parse_cmd(args[2 + i], envp), envp);
			perror("exec failed");
			exit(1);
		}
		else if (pid < 0)
		{
			perror("fork failed");
			return (-1);
		}
		else
		{
			if (i > 0)
				close(pipes[i - 1][0]);
			if (i < ncmds - 1)
				close(pipes[i][1]);
		}
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


/* 
int	exec_all(int *file, int (*pipes)[2], char **args, char **envp)
{
	pid_t	pid;
	int		status;
	int		ncmds;
	int		i;

	ncmds = 0;
	while (args[ncmds])
		ncmds++;
	ncmds -= 3;
	ft_printf("DEBUG: ncmds=%d, num_args=%d\n", ncmds, ncmds + 3);
	i = 0;
	while (i < ncmds)
	{
		pid = fork();
		printf("DEBUG: i=%d, pid=%d, meu_pid=%d\n", i, pid, getpid());
		if (pid == 0)
		{
			printf("DEBUG: FILHO i=%d, meu_pid=%d\n", i, getpid());
			if (i == 0)
			{
				printf("DEBUG: processo %d, i=%d, configurando pipes\n", getpid(), i);
				dup2(file[0], STDIN_FILENO);
				dup2(pipes[0][1], STDOUT_FILENO);
				closer_pipes(pipes, ncmds, 0);
			}
			else if (i == ncmds - 1)
			{
				printf("DEBUG: processo %d, i=%d, configurando pipes\n", getpid(), i);
				dup2(pipes[i - 1][0], STDIN_FILENO);
				dup2(file[1], STDOUT_FILENO);
				closer_pipes(pipes, ncmds, i);
			}
			else
			{
				printf("DEBUG: processo %d, i=%d, configurando pipes\n", getpid(), i);
				dup2(pipes[i - 1][0], STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
				closer_pipes(pipes, ncmds, i);
			}
			exec_cmd(parse_cmd(args[2 + i], envp), envp);
			perror("Error exec: ");
			return (-1);
		}
		else if (pid < 0)
			perror("Error Fork: ");
		else
		{
			printf("DEBUG: PAI i=%d, fechando pipes\n", i);
			if (i > 0)
				close(pipes[i - 1][0]);
			if (i < ncmds - 1)
				close(pipes[i][0]);
		}
		i++;
	}
	i = 0;
	while (i < ncmds)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	return (0);
} */
