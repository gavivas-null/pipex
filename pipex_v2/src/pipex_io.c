/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:31:15 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 21:27:18 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	open_infile(t_pipex *px, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(path);
		px->infile = open("/dev/null", O_RDONLY);
		if (px->infile == -1)
			px->err = 1;
	}
	else
		px->infile = fd;
}

int	open_outfile_mode(t_pipex *px, char *path, int append)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(path, flags, 0644);
	if (fd == -1)
	{
		perror(path);
		px->err = 1;
		return (-1);
	}
	px->outfile = fd;
	return (fd);
}

void	create_pipe(t_pipex *px)
{
	if (pipe(px->pipefd) == -1)
	{
		exit_with_error("pipe", NULL, NULL, EXIT_FAILURE);
	}
}

static int	is_limiter(char *line, char *limiter)
{
	int	len_lim;

	len_lim = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, len_lim) == 0
		&& line[len_lim] == '\n'
		&& line[len_lim + 1] == '\0')
		return (1);
	return (0);
}

int	heredoc_make_pipe(t_pipex *px, char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		px->err = 1;
		return (-1);
	}
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (is_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
