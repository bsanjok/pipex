/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:36:39 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 13:32:34 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_split_alloc(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_bins(t_pipe *pipex)
{
	int	i;

	i = 0;
	if (pipex->valid_bins)
	{
		while (i < pipex->commands)
		{
			free(pipex->valid_bins[i]);
			i++;
		}
		free(pipex->valid_bins);
		pipex->valid_bins = NULL;
	}
}

void	free_and_exit(t_pipe *pipex)
{
	int	i;

	i = 0;
	if (pipex->has_here_doc == 1)
		unlink("here_doc");
	if (pipex->path)
		free_split_alloc(pipex->path);
	free_bins(pipex);
	if (pipex->cmd_children)
	{
		while (pipex->cmd_children[i])
		{
			free_split_alloc(pipex->cmd_children[i]);
			i++;
		}
		if (pipex->cmd_children)
		{
			free (pipex->cmd_children);
			pipex->cmd_children = NULL;
		}
	}
	free(pipex);
}

void	checkleaks(void)
{
	system("leaks pipex");
}
