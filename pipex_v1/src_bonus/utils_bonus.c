/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:22 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/17 19:26:57 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
