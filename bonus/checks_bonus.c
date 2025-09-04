/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:39:02 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/04 13:39:30 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_here_d(char *here_d)
{
	if (ft_strncmp(here_d, "here_doc", 9) == 0)
		return (1);
	return (0);
}

int	check_args(char **args, int num, int file[2])
{
	if (num < 4)
		return (1);
	if (setup_here_d(args, file, num))
		return (1);
	return (0);
}
