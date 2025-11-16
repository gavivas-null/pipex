/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:16:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 20:11:15 by gavivas-         ###   ########.fr       */
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
