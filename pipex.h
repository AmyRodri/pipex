/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:11:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/26 12:01:27 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/srcs/includes/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_cmd
{
	char	*path;
	char	**argv;
}	t_cmd;

t_cmd	*parse_cmd(char *arg);
void	exec_cmd(t_cmd *cmd, char **envp);
int		exec_first(int *file, int *fd, t_cmd *cmd, char **envp);
int		exec_segund(int *file, int *fd, t_cmd *cmd, char **envp);

#endif