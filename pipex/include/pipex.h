/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:17:16 by gavivas-          #+#    #+#             */
/*   Updated: 2025/06/16 21:21:53 by gavivas-         ###   ########.fr       */
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
# include <sys/wait.h>

# ifndef ERRORARGS
#  define ERRORARGS "Error. Número incorrecto de argumentos.\n"
# endif

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		status_b;
	int		pipefd[2];
	int		prev_fd;
	char	**envp;
}	t_pipex;

//---------------------error---------------------
int		needs_shell(char *cmd);
void	exit_with_error(char *msg, char **split, char *to_free, int code);
void	cmd_error(char *cmd, char **split);

//---------------------init---------------------
void	open_infile(t_pipex *px, char *path);
void	open_outfile(t_pipex *px, char *path);
void	create_pipe(t_pipex *px);

//---------------------exec---------------------
void	child_a(t_pipex *px, char *cmd, char **envp);
void	child_b(t_pipex *px, char *cmd, char **envp);

//---------------------pipex---------------------
void	assing_child(t_pipex	*px, char **args, char **envp);

//---------------------utils---------------------
char	*get_cmd_path(char *cmd, char **envp, int i);
char	*get_path_value(char **envp);
char	**get_paths_array(char **envp);
char	*find_executable_path(char **paths, char *cmd, int i);
void	exec_cmd(char *cmd, char **envp);

//---------------------bonus---------------------
void	handle_command(t_pipex *px, char *cmd, int input_fd, int output_fd);

#endif
