/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:03:31 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 13:13:31 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../lib/libft/include/ft_printf.h"

typedef struct s_pipe
{
	char	***cmd_children;
	char	**path;
	char	**valid_bins;
	int		pipe_a[2];
	int		pipe_b[2];
	int		args;
	int		commands;
	int		has_here_doc;
}	t_pipe;

void	middle_child_process(t_pipe *pipex, int index);
void	last_child_process(t_pipe *pipex, int index, char **argv);
void	first_child_process(t_pipe *pipex, char **argv);
void	parent_closing(t_pipe *pipex, int i, int pid);
void	process_decider(t_pipe *pipex, char **env, char **argv, int i);
char	*get_valid_bin(t_pipe *pipex, char *command);
char	**get_final_path(char **env);
char	**get_path_from_env(char **env);
int		compare_cmd(char *src, char *dst);
void	execute(t_pipe *pipex, char *valid_bin, char **command, char **env);
void	init_children(t_pipe *pipex, char **env, char **argv);
int		init_cmd_bin(t_pipe *pipex, char **argv);
char	**if_awk(char *argv);
void	check_cmd(t_pipe *pipex, char **argv, int i, int j);
void	ft_dup(t_pipe *pipex, int src, int dst);
int		compare_cmd(char *src, char *dst);
void	is_here_doc(t_pipe *pipex, char *limiter);

//FREE
void	free_bins(t_pipe *pipex);
void	free_and_exit(t_pipe *pipex);
void	free_split_alloc(char **str);

void	checkleaks(void);

#endif