/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/16 21:08:12 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (argc < 5)
		return (ft_putstr_fd(ERRORARGS, 2), 1);
	px.envp = envp;
	open_infile(&px, args[1]);
	open_outfile(&px, args[argc - 1]);
	create_pipe(&px);
	assing_child(&px, args, envp);
	return (WEXITSTATUS(px.status_b));
}
