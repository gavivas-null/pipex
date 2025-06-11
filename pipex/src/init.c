/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:42:24 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/11 16:22:27 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_infile(t_pipex *px, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
	px->infile = fd;
}

void	open_outfile(t_pipex *px, char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}
	px->outfile = fd;
}

void	create_pipe(t_pipex *px)
{
	if (pipe(px->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
