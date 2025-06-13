/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/13 22:40:32 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_a(t_pipex *px, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(px->infile, STDIN_FILENO) == -1)
		exit_with_error("dup2 infile", NULL, NULL, 1);
	if (dup2(px->pipefd[1], STDOUT_FILENO) == -1)
		exit_with_error("dup2 pipefd", NULL, NULL, 1);
	close(px->infile);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		exit_with_error("split", NULL, NULL, 1);
	path = get_cmd_path(cmd_args[0], envp, 0);
	if (!path)
		exit_with_error("path not found", cmd_args, NULL, 127);
	if (execve(path, cmd_args, envp) == -1)
		exit_with_error("execve", cmd_args, path, 1);
}

void	child_b(t_pipex *px, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(px->pipefd[0], STDIN_FILENO) == -1)
		exit_with_error("dup2 pipefd", NULL, NULL, 1);
	if (dup2(px->outfile, STDOUT_FILENO) == -1)
		exit_with_error("dup2 outfile", NULL, NULL, 1);
	close(px->outfile);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		exit_with_error("split", NULL, NULL, 1);
	path = get_cmd_path(cmd_args[0], envp, 0);
	if (!path)
		exit_with_error("path not found", cmd_args, NULL, 127);
	if (execve(path, cmd_args, envp) == -1)
		exit_with_error("execve", cmd_args, path, 1);
}
