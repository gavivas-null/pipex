/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:20:11 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/23 20:31:01 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpipex.h>

char	*get_path_value(char **envp)
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

char	**get_paths_array(char **envp)
{
	char	*path_val;
	char	**paths;

	path_val = get_path_value(envp);
	if (!path_val)
		return (NULL);
	paths = ft_split(path_val, ':');
	if (!paths)
		exit_with_error("split paths", NULL, NULL, 1);
	return (paths);
}

char	*find_executable_path(char **paths, char *cmd, int i)
{
	char	*temp_path;
	char	*full_path;

	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		if (!temp_path || !full_path)
			exit_with_error("strjoin", paths, temp_path, 1);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	paths = get_paths_array(envp);
	if (!paths)
		return (NULL);
	result = find_executable_path(paths, cmd, i);
	ft_free_split(paths);
	return (result);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		exit_with_error("command not found", cmd_args, NULL, 127);
	path = get_cmd_path(cmd_args[0], envp, 0);
	if (!path)
		cmd_error(cmd_args[0], cmd_args);
	if (execve(path, cmd_args, envp) == -1)
		exit_with_error("execve", cmd_args, path, 1);
}
