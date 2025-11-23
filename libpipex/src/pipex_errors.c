/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:30:49 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/23 20:30:51 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpipex.h>

void	exit_with_error(char *msg, char **split, char *to_free, int code)
{
	perror(msg);
	if (split)
		ft_free_split(split);
	if (to_free)
		free(to_free);
	exit(code);
}

void	cmd_error(char *cmd, char **split)
{
	char	*msg;

	msg = ft_strjoin("exec: ", cmd);
	if (!msg)
	{
		if (split)
			ft_free_split(split);
		exit(127);
	}
	perror(msg);
	free(msg);
	if (split)
		ft_free_split(split);
	exit(127);
}
