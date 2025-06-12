/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/12 21:26:33 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child1(t_pipex *px, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(px->infile, STDIN_FILENO) == -1)
		perror("Error infile");
	if (dup2(px->pipefd[1], STDOUT_FILENO) == -1)
		perror("Error pipefd");
	close(px->infile);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
	{
		perror("path not found");
		exit(1);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	child2(t_pipex *px, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(px->pipefd[0], STDIN_FILENO) == -1)
		perror("Error pipefd");
	if (dup2(px->outfile, STDOUT_FILENO) == -1)
		perror("Error outfile");
	close(px->outfile);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
	{
		perror("Path not found");
		exit(1);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}
