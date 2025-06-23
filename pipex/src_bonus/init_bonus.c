/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:36:17 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/23 16:36:08 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_infile(t_pipex *px, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex_bonus: ", 2);
		perror(path);
		px->infile = open("/dev/null", O_RDONLY);
		if (px->infile == -1)
			px->err = 1;
	}
	else
		px->infile = fd;
}

int	open_outfile_bonus(t_pipex *px, char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex_bonus: ", 2);
		perror(path);
		px->err = 1;
	}
	return (fd);
}

void	create_pipe(t_pipex *px)
{
	if (pipe(px->pipefd) == -1)
	{
		exit_with_error("pipe", NULL, NULL, EXIT_FAILURE);
	}
}
