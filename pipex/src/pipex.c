/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:31 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/14 18:49:59 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	assing_child(t_pipex	*px, char **args, char **envp)
{
	int		pid_a;
	int		pid_b;

	pid_a = fork();
	if (pid_a == 0)
		child_a(px, args[2], envp);
	if (pid_a < 0)
	{
		exit_with_error("fork a", NULL, NULL, 1);
	}
	pid_b = fork();
	if (pid_b == 0)
		child_b(px, args[3], envp);
	if (pid_b < 0)
	{
		exit_with_error("fork b", NULL, NULL, 1);
	}
	if (px->pipefd[0] >= 0)
		close(px->pipefd[0]);
	if (px->pipefd[1] >= 0)
		close(px->pipefd[1]);
	waitpid(pid_a, NULL, 0);
	waitpid(pid_b, &px->status_b, 0);
}

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (argc != 5)
		return (ft_putstr_fd(ERRORARGS, 2), 1);
	px.pipefd[0] = -1;
	px.pipefd[1] = -1;
	open_infile(&px, args[1]);
	open_outfile(&px, args[4]);
	create_pipe(&px);
	assing_child(&px, args, envp);
	return (WEXITSTATUS(px.status_b));
}
