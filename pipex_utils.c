/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:59:59 by amyrodri          #+#    #+#             */
/*   Updated: 2025/09/01 17:14:41 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*parse_cmd(char *arg, char **envp)
{
	t_cmd	*cmd;
	char	**splited;
	char	*path;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	splited = ft_split(arg, ' ');
	if (!splited || !splited[0])
		return (NULL);
	path = find_cmd(splited[0], envp);
	cmd->path = path;
	cmd->argv = splited;
	return (cmd);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char *cmd, char **envp)
{
	char	*path_envp;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_envp = get_path(envp);
	paths = ft_split(path_envp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	closer(int *fds, int len)
{
	int	i;

	i = 0;
	while (i < len)
		close(fds[i++]);
}
