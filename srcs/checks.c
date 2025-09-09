/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:39:02 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/09 16:33:23 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_here_d(char *here_d)
{
	if (ft_strncmp(here_d, "here_doc", 9) == 0)
		return (1);
	return (0);
}

static int	check_num_args(int num, char **args)
{
	if (!check_here_d(args[1]))
	{
		if (num < 4)
			return (1);
	}
	else
	{
		if (num < 5)
			return (1);
	}
	return (0);
}

int	check_args(char **args, int num, int file[2])
{
	if (check_num_args(num, args))
		return (1);
	if (setup_here_d(args, file, num))
		return (1);
	return (0);
}
