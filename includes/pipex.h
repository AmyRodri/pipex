/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:11:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/09 19:50:35 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/srcs/includes/libft.h"
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

// checks.c
int		check_here_d(char *here_d);
int		check_args(char **args, int num, int file[2]);

// exec.c
int		exec_all(int *file, int (*pipes)[2], char **args, char **envp);

// here_doc.c
int		setup_here_d(char **args, int file[2], int num);
int		start_pipes(int (*pipes)[2], int num);

// pipex_fd.c
void	closer_pipes(int (*pipes)[2], int len, int j);
void	closer_files(int *files, int len);
int 	free_exit(int (*pipes)[2], int ret);
int		wait_closer(int *file, int n_cmds);

// utils.c
t_cmd	*parse_cmd(char *arg, char **envp);
int		ft_argslen(char **arg);

// pipex.c
// main
#endif