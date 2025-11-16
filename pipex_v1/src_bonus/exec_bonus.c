/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:14 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/23 17:36:07 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	handle_command(t_pipex *px, char *cmd, int input_fd, int output_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit_with_error("dup2 input", NULL, NULL, 1);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		exit_with_error("dup2 output", NULL, NULL, 1);
	close(input_fd);
	close(output_fd);
	close(px->infile);
	close(px->outfile);
	close(px->pipefd[0]);
	exec_cmd(cmd, px->envp);
}
