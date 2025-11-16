/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:57:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 20:13:55 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	init_all(t_pipex *px, int argc, char **args, char **envp)
{
	px->infile = -1;
	px->outfile = -1;
	px->pipefd[0] = -1;
	px->pipefd[1] = -1;
	px->prev_fd = -1;
	px->status_b = 0;
	px->err = 0;
	px->envp = envp;
	px->is_heredoc = is_heredoc(argc, args);
	if (!min_args_ok(px->is_heredoc, argc))
		return (ft_putstr_fd(ERRORARGS, 2), EXIT_FAILURE);
	px->cmd_start = first_cmd_index(px->is_heredoc);
	px->outfile = open_outfile(px, args[argc - 1]);
	open_infile(px, args[1]);
	if (px->err == 1)
	{
		close(px->infile);
		close(px->outfile);
		exit(1);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (init_all(&px, argc, args, envp) != 0)
		return (EXIT_FAILURE);
	execute_pipeline(&px, args, argc);
	close(px.infile);
	close(px.outfile);
	return (WEXITSTATUS(px.status_b));
}
