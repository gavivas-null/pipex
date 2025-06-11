/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:17:16 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/11 20:37:44 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../Libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

# ifndef ERRORARGS
#  define ERRORARGS "Error. Número incorrecto de argumentos.\n"
# endif

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	char	**envp;
}	t_pipex;

//---------------------init---------------------
void	open_infile(t_pipex *px, char *path);
void	open_outfile(t_pipex *px, char *path);
void	create_pipe(t_pipex *px);

//---------------------exec---------------------
void	child1(t_pipex *px, char *cmd, char **envp);
void	child2(t_pipex *px, char *cmd, char **envp);


char	*get_cmd_path(char *cmd, char **envp);

#endif
