/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:11:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/04 13:40:25 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

int		check_here_d(char *here_d);
void	write_here_doc(int fd, char *limiter);
void	here_d_cmds(char **args, int *n_cmds, int *start_cmds);

void	exec_cmd(t_cmd *cmd, char **envp);
void	parent_exec(int (*pipes)[2], int n_cmds, int i, pid_t pid);
int		exec_all(int *file, int (*pipes)[2], char **args, char **envp);

void	closer_pipes(int (*pipes)[2], int len, int j);
void	closer_files(int *files, int len);
void	setup_pipes_fds(int *file, int (*pipes)[2], int ncmds, int i);
int		wait_closer(int *file, int n_cmds);

t_cmd	*parse_cmd(char *arg, char **envp);
char	*get_path(char **envp);
char	*find_cmd(char *cmd, char **envp);
int		ft_argslen(char **arg);

int		check_args(char **args, int num, int file[2]);
int		check_here_d(char *here_d);

int		start_pipes(int (*pipes)[2], int num);
int		setup_here_d(char **args, int file[2], int num);
void	write_here_doc(int fd, char *limiter);

#endif