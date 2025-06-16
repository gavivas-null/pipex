/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/16 22:15:55 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_pipeline(t_pipex *px, char **args, int argc)
{
	int	i;
	int	pid;

	i = 2;
	px->prev_fd = px->infile;
	while (i < (argc - 1))
	{
		if (i == (argc -2))
		{
			pid = fork();
			if (pid == 0)
				handle_command(px, args[i], px->prev_fd, px->outfile);
			if (pid < 0)
				exit_with_error("fork pid", NULL, NULL, 1);
			if (px->pipefd[0] >= 0)
				close(px->pipefd[0]);
			close(px->prev_fd);
		}
		else
		{
			create_pipe(&px);
			pid = fork();
			if (pid == 0)
				handle_command(px, args[i], px->prev_fd, px->pipefd[1]);
			if (pid < 0)
				exit_with_error("fork pid", NULL, NULL, 1);
			if (px->pipefd[1] >= 0)
				close(px->pipefd[1]);
			close(px->prev_fd);
			px->prev_fd = px->pipefd[0];
		}
		i++;
	}
}

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (argc < 5)
		return (ft_putstr_fd(ERRORARGS, 2), 1);
	px.pipefd[0] = -1;
	px.pipefd[1] = -1;
	px.envp = envp;
	open_infile(&px, args[1]);
	open_outfile(&px, args[argc - 1]);
	return (WEXITSTATUS(px.status_b));
}
