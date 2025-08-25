/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/25 15:37:55 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* char	**parse_cmd(int n, char *cmds)
{
	char	**cmd_split;
	char	*comand;

	cmd_split = ft_split(cmds, ' ');
	if (cmd_split[1])
	{
		
	}
	comand = ft_strjoin("/bin/", cmd_split[0]);
	
} */

int	main(int num, char **args)
{
	int		file1;
	int		file2;
	char	**cmd1;
	char	**cmd2;
	pid_t	pid;

	if (num == 5)
	{
		file1 = open(args[1], O_RDONLY);
		dup2(file1, STDIN_FILENO);
		close(file1);
		cmd1 = ft_split(args[2], ' ');
		cmd2 = ft_split(args[3], ' ');
		file2 = open(args[num - 1], O_WRONLY);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		pid = fork();
		if (pid < 0)
		{
			perror("fork não concluido");
			return (1);
		}
		else if (pid == 0)
		{
			char *comand = ft_strjoin("/bin/", cmd1[0]);
			char *test[] = {comand, cmd1[1], NULL};
			char *envp[] = {NULL};

			if (execve(comand, test, envp) == -1)
			{
				perror("erro ao exetutar o comando");
				return (1);
			}
		}
	}
	return (0);
}
