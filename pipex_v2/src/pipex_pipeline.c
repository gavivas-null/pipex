/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:31:26 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 22:35:57 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_last_command(t_pipex *px, char *cmd, int *pid)
{
	*pid = fork();
	if (*pid == 0)
		handle_command(px, cmd, px->prev_fd, px->outfile);
	if (*pid < 0)
		exit_with_error("fork pid", NULL, NULL, 1);
	if (px->pipefd[0] >= 0)
		close(px->pipefd[0]);
	close(px->prev_fd);
}

void	exec_middle_command(t_pipex *px, char *cmd, int *pid)
{
	create_pipe(px);
	*pid = fork();
	if (*pid == 0)
		handle_command(px, cmd, px->prev_fd, px->pipefd[1]);
	if (*pid < 0)
		exit_with_error("fork pid", NULL, NULL, 1);
	if (px->pipefd[1] >= 0)
		close(px->pipefd[1]);
	close(px->prev_fd);
	px->prev_fd = px->pipefd[0];
}

void	execute_pipeline(t_pipex *px, char **args, int argc)
{
	int	i;
	int	pid;

	i = px->cmd_start;
	px->prev_fd = px->infile;
	while (i < (argc - 1))
	{
		if (i == (argc -2))
			exec_last_command(px, args[i], &pid);
		else
			exec_middle_command(px, args[i], &pid);
		i++;
	}
	waitpid(pid, &px->status_b, 0);
	while (wait(NULL) > 0)
		;
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
