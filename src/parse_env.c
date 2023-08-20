/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:37:03 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 12:25:24 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_path_from_env(char **env)
{
	int		i;
	char	*path;
	char	**holder;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=/", 6))
			break ;
		i++;
	}
	path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	if (!path)
		return (0);
	holder = ft_split(path, ':');
	if (!holder)
	{
		free (path);
		return (0);
	}
	free (path);
	return (holder);
}

char	**get_final_path(char **env)
{
	int		i;
	char	**result;
	char	**holder;

	i = 0;
	holder = get_path_from_env(env);
	if (!holder)
		return (0);
	while (holder[i])
		i++;
	result = ft_calloc((i + 1), sizeof(char *));
	if (!result)
	{
		free_split_alloc(holder);
		return (0);
	}
	i = -1;
	while (holder[++i])
		result[i] = ft_strjoin(holder[i], "/");
	free_split_alloc(holder);
	result[i] = NULL;
	return (result);
}

char	*get_valid_bin(t_pipe *pipex, char *command)
{
	int		i;
	char	*current_bin;

	i = -1;
	while (pipex->path[++i])
	{
		current_bin = ft_strjoin(pipex->path[i], command);
		if (access(current_bin, F_OK | X_OK) == 0)
			return (current_bin);
		free(current_bin);
	}
	current_bin = malloc((ft_strlen(command) + 1) * sizeof(char *));
	if (!current_bin)
		return (0);
	ft_strlcpy(current_bin, command, ft_strlen(command) + 1);
	return (current_bin);
}

int	init_cmd_bin(t_pipe *pipex, char **argv)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	if (compare_cmd(argv[1], "here_doc") == 1)
		j = 3;
	pipex->valid_bins = (char **)malloc((pipex->commands + 1) \
	* sizeof (char *));
	if (!pipex->valid_bins)
		return (-1);
	pipex->cmd_children = (char ***)malloc((pipex->commands + 1) \
	* sizeof (char **));
	if (!pipex->cmd_children)
		return (-1);
	while (++i < (pipex->commands))
	{
		pipex->cmd_children[i] = ft_split(argv[j], ' ');
		check_cmd(pipex, argv, i, j);
		pipex->valid_bins[i] = get_valid_bin(pipex, pipex->cmd_children[i][0]);
		j++;
	}
	pipex->cmd_children[i] = NULL;
	pipex->valid_bins[i] = NULL;
	return (0);
}
