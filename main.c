/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:08:15 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/25 11:43:27 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int num, char **args)
{
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	pid_t	pid;

	if (num == 5)
	{
		pid = fork();
		file1 = args[1];
		cmd1 = args[2];
		cmd2 = args[3];
		file2 = args[4];
		ft_printf("%s -> %s -> %s -> %s\n", file1, cmd1, cmd2, file2);
	}
	return (0);
}
