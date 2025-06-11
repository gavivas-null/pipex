/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:31 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/11 19:57:53 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **args, char **envp)
{
	t_pipex	px;

	if (argc != 5)
		return (ft_putstr_fd(ERRORARGS, 2), 1);
	open_infile(&px, args[1]);
	open_outfile(&px, args[4]);
	create_pipe(&px);
	return (0);
}
