/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/01 19:39:31 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int num, char **args, char **envp)
{
	int	(**pipes)[2];
	int	file[2];
	int	i;

	if (num <= 5)
		return (1);
	file[0] = open(args[1], O_RDONLY);
	file[1] = open(args[num - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file[0] < 0 || file[1] < 0)
		return (perror("Error file"), 1);
	pipes = malloc((num - 4) * sizeof(*pipes));
	i = 0;
	while (num - 4 > i)
	{
		if (pipe(pipes[i]) == -1)
			return (perror("Error pipe"), 1);
		i++;
	}
	exec_all(file, pipes, args, envp);
	closer_pipes(pipes, num - 4);
	closer_files(file, 2);
	free(pipes);
	return (0);
}
