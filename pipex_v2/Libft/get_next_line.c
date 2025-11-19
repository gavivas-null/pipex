/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:47:45 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/19 20:22:20 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_process_line(char **data, char *endline)
{
	char	*newline;
	char	*tmp;
	size_t	rest_len;

	newline = ft_gnl_substr(*data, 0, (endline - *data) + 1);
	rest_len = ft_gnl_strlen(endline + 1);
	if (rest_len > 0)
	{
		tmp = ft_gnl_substr(*data, (endline - *data) + 1, rest_len);
		free(*data);
		*data = tmp;
	}
	else
	{
		free(*data);
		*data = NULL;
	}
	return (newline);
}

static char	*ft_extract_line(char **data, char *buff, ssize_t count)
{
	char	*tmp;
	char	*endline;
	char	*newline;

	buff[count] = '\0';
	tmp = ft_gnl_strjoin(*data, buff);
	if (!tmp)
		return (free(buff), NULL);
	*data = tmp;
	endline = ft_gnl_strchr(*data, '\n');
	if (endline)
	{
		newline = ft_process_line(data, endline);
		if (!newline)
		{
			free(buff);
			return (NULL);
		}
		return (newline);
	}
	return (NULL);
}

static char	*ft_rest_of_data(char **data)
{
	char	*newline;

	if (*data && **data)
	{
		newline = ft_gnl_substr(*data, 0, ft_gnl_strlen(*data));
		free(*data);
		*data = NULL;
		return (newline);
	}
	else if (*data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}

static char	*ft_while(int fd, char **data, char *buff)
{
	ssize_t		count;
	char		*newline;

	while (1)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if ((count < 0) || (count == 0 && !ft_gnl_strchr(*data, '\n')))
		{
			free(buff);
			if (count < 0)
			{
				free(*data);
				*data = NULL;
				return (NULL);
			}
			break ;
		}
		newline = ft_extract_line(data, buff, count);
		if (newline)
			return (free(buff), newline);
	}
	return (ft_rest_of_data(data));
}

char	*get_next_line(int fd)
{
	static char	*data = NULL;
	char		*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	return (ft_while(fd, &data, buff));
}
