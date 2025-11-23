/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:48:58 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/12 21:29:54 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	px.outfile = open_outfile(&px, args[argc - 1]);
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
