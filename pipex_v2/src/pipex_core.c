/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:30:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/12 21:29:36 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
