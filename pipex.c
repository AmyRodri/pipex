/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 14:38:15 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int num, char **args, char **envp)
{
	int		file[2];
	int		fd[2];
	pid_t	pid[2];

	if (num != 5)
		return (1);
	file[0] = open(args[1], O_RDONLY);
	file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file[0] < 0 || file[1] < 0 || pipe(fd) == -1)
		return (perror("Error"), 1);
	pid[0] = fork();
	if (pid[0] == 0)
		exec_first(file, fd, parse_cmd(args[2], envp), envp);
	pid[1] = fork();
	if (pid[1] == 0)
		exec_segund(file, fd, parse_cmd(args[3], envp), envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
