/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:48:27 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 12:22:40 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute(t_pipe *pipex, char *valid_bin, char **command, char **env)
{
	if (valid_bin)
		execve(valid_bin, command, env);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_and_exit(pipex);
	exit(127);
}

void	init_children(t_pipe *pipex, char **env, char **argv)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < (pipex->commands))
	{
		if (!(i % 2))
			if (pipe(pipex->pipe_a) < 0)
				exit(127);
		if (i % 2)
			if (pipe(pipex->pipe_b) < 0)
				exit(127);
		pid = fork();
		if (pid < 0)
		{
			free_and_exit(pipex);
			perror("Fork: ");
		}
		else if (pid == 0)
			process_decider(pipex, env, argv, i);
		else
			parent_closing(pipex, i, pid);
	}
}

void	parent_closing(t_pipe *pipex, int i, int pid)
{
	int	status;

	if (i == 0)
		close (pipex->pipe_a[1]);
	else if (i == pipex->commands - 1 && i % 2)
		close (pipex->pipe_b[1]);
	else if (i == pipex->commands - 1 && !(i % 2))
		close (pipex->pipe_a[1]);
	else
	{
		if (i % 2)
		{
			close (pipex->pipe_a[0]);
			close (pipex->pipe_b[1]);
		}
		else
		{
			close (pipex->pipe_a[1]);
			close (pipex->pipe_b[0]);
		}
		waitpid(pid, &status, 0);
	}
}
