/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 17:13:44 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int num, char **args, char **envp)
{
	int		file[2];
	int		fd[2];

	if (num != 5)
		return (1);
	file[0] = open(args[1], O_RDONLY);
	file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file[0] < 0 || file[1] < 0)
		return (perror("Error file"), 1);
	if (pipe(fd) == -1)
		return (perror("Error pipe"), 1);
	exec_all(file, fd, args, envp);
	closer(fd, 2);
	closer(file, 2);
	return (0);
}
