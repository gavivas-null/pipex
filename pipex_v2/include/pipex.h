/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:37:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/11/16 21:16:11 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
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
	int		err;
	int		is_heredoc;
	int		cmd_start;
	char	**envp;
}	t_pipex;

//---------------------pipex---------------------
int		init_all(t_pipex*px, int argc, char **args, char **envp);
char	*get_cmd_path(char *cmd, char **envp, int i);
char	*find_executable_path(char **paths, char *cmd, int i);
char	**get_paths_array(char **envp);
char	*get_path_value(char **envp);
void	open_infile(t_pipex *px, char *path);
void	create_pipe(t_pipex *px);
void	cmd_error(char *cmd, char **split);
void	exit_with_error(char *msg, char **split, char *to_free, int code);
void	exec_cmd(char *cmd, char **envp);
void	handle_command(t_pipex *px, char *cmd, int input_fd, int output_fd);
void	exec_last_command(t_pipex *px, char *cmd, int *pid);
void	exec_middle_command(t_pipex *px, char *cmd, int *pid);
void	execute_pipeline(t_pipex *px, char **args, int argc);

//----------------here_doc-------------------
int		is_heredoc(int argc, char **argv);
int		first_cmd_index(int is_hd);
int		min_args_ok(int is_hd, int argc);
int		heredoc_make_pipe(t_pipex *px, char *limiter);
int		open_outfile_mode(t_pipex *px, char *path, int append);

#endif