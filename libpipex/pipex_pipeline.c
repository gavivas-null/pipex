/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:31:26 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/23 20:31:06 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpipex.h>

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

	i = 2;
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
