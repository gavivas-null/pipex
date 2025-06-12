/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:27 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/12 21:37:17 by gavivas-         ###   ########.fr       */
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

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*temp_path;
	char	*path_value;
	char	*full_path;

	i = 0;
	path_value = get_path_value(envp);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
