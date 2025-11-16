/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:31:26 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 20:29:42 by gavivas-         ###   ########.fr       */
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
