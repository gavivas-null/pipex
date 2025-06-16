/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:04:49 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/16 19:46:15 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	if (split)
		ft_free_split(split);
	exit(127);
}

int	needs_shell(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"' || cmd[i] == '|'
			|| cmd[i] == ';' || cmd[i] == '<' || cmd[i] == '>'
			|| cmd[i] == '&' || cmd[i] == '$' || cmd[i] == '('
			|| cmd[i] == ')')
			return (1);
		i++;
	}
	return (0);
}
