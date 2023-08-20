/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:38:02 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 13:05:14 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_dup(t_pipe *pipex, int src, int dst)
{
	if (dup2(src, dst) == -1)
	{
		perror("dup");
		free_and_exit(pipex);
		exit(127);
	}
}

void	process_decider(t_pipe *pipex, char **env, char **argv, int i)
{
	if (i == 0)
		first_child_process(pipex, argv);
	else if (i == (pipex->commands - 1))
		last_child_process(pipex, i, argv);
	else
		middle_child_process(pipex, i);
	execute(pipex, pipex->valid_bins[i], pipex->cmd_children[i], env);
}

void	first_child_process(t_pipe *pipex, char **argv)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), argv[1]);
		free_and_exit(pipex);
		exit (127);
	}
	close(pipex->pipe_a[0]);
	ft_dup(pipex, infile, STDIN_FILENO);
	ft_dup(pipex, pipex->pipe_a[1], STDOUT_FILENO);
	close(pipex->pipe_a[1]);
	close (infile);
}

void	middle_child_process(t_pipe *pipex, int index)
{
	if (index % 2)
	{
		ft_dup(pipex, pipex->pipe_a[0], STDIN_FILENO);
		ft_dup(pipex, pipex->pipe_b[1], STDOUT_FILENO);
		close(pipex->pipe_a[0]);
		close(pipex->pipe_b[1]);
	}
	if (!(index % 2))
	{
		ft_dup(pipex, pipex->pipe_b[0], STDIN_FILENO);
		ft_dup(pipex, pipex->pipe_a[1], STDOUT_FILENO);
		close(pipex->pipe_b[0]);
		close(pipex->pipe_a[1]);
	}
}

void	last_child_process(t_pipe *pipex, int index, char **argv)
{
	int	outfile;

	outfile = open(argv[pipex->args - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), argv[pipex->args - 1]);
		free_and_exit(pipex);
		exit (127);
	}
	if (index % 2)
	{
		close (pipex->pipe_a[1]);
		ft_dup(pipex, outfile, STDOUT_FILENO);
		ft_dup(pipex, pipex->pipe_a[0], STDIN_FILENO);
		close (pipex->pipe_a[0]);
	}
	if (!(index % 2))
	{
		close (pipex->pipe_b[1]);
		ft_dup(pipex, outfile, STDOUT_FILENO);
		ft_dup(pipex, pipex->pipe_b[0], STDIN_FILENO);
		close (pipex->pipe_b[0]);
	}
	close (outfile);
}
