/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:16:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 22:38:47 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	is_heredoc(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (1);
	return (0);
}

int	first_cmd_index(int is_hd)
{
	if (is_hd)
		return (3);
	return (2);
}

int	min_args_ok(int is_hd, int argc)
{
	if (is_hd && argc >= 6)
		return (1);
	if (!is_hd && argc >= 5)
		return (1);
	return (0);
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
