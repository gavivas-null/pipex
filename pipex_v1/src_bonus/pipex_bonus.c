/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/23 19:06:21 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (argc < 5)
		return (ft_putstr_fd(ERRORARGS, 2), 1);
	px.pipefd[0] = -1;
	px.pipefd[1] = -1;
	px.status_b = 0;
	px.err = 0;
	px.envp = envp;
	px.outfile = open_outfile_bonus(&px, args[argc - 1]);
	open_infile(&px, args[1]);
	if (px.err == 1)
	{
		close(px.infile);
		close(px.outfile);
		exit(1);
	}
	execute_pipeline(&px, args, argc);
	close(px.infile);
	close(px.outfile);
	return (WEXITSTATUS(px.status_b));
}
