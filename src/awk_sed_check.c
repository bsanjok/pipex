/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk_sed_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:13:18 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/01 16:34:54 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_cmd(t_pipe *pipex, char **argv, int i, int j)
{
	if (compare_cmd(pipex->cmd_children[i][0], "awk") == 1)
	{
		free_split_alloc(pipex->cmd_children[i]);
		pipex->cmd_children[i] = NULL;
		pipex->cmd_children[i] = if_awk(argv[j]);
	}
	if (compare_cmd(pipex->cmd_children[i][0], "sed") == 1)
	{
		free_split_alloc(pipex->cmd_children[i]);
		pipex->cmd_children[i] = NULL;
		pipex->cmd_children[i] = if_awk(argv[j]);
	}
}

char	*for_norm(char *argv, int i)
{
	while (*argv == ' ' || *argv == '\'' || *argv == '\"')
	{
		if (*argv == '\'' || *argv == '\"')
		{
			argv++;
			break ;
		}
		argv++;
	}
	i = ft_strlen(argv) - 1;
	while (argv[i] == ' ' || argv[i] == '\'' || argv[i] == '\"')
	{
		if (argv[i] == '\'' || argv[i] == '\"')
		{
			argv[i] = '\0';
			break ;
		}
		argv[i] = '\0';
		i--;
	}
	return (argv);
}

char	**if_awk(char *argv)
{
	char	**result;
	int		i;

	i = 0;
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (0);
	result[0] = malloc(4 * sizeof(char));
	while (i <= 2)
	{
		result[0][i] = *argv;
		argv++;
		i++;
	}
	result[0][i] = '\0';
	argv = for_norm(argv, i);
	result[1] = malloc((ft_strlen(argv) + 1) * sizeof(char));
	if (!result[1])
		return (0);
	ft_strlcpy(result[1], argv, ft_strlen(argv) + 1);
	result[2] = 0;
	return (result);
}

int	compare_cmd(char *src, char *dst)
{
	int	i;

	i = 0;
	if (src[ft_strlen(src) - 1] == '\n')
		src[ft_strlen(src) - 1] = '\0';
	if (src[i] == '\n' || ft_strlen(src) != ft_strlen(dst))
		return (0);
	while (src[i] && src[i] != '\n')
	{
		if (src[i] != dst[i] || (dst[i] == '\0' && src[i]))
			return (0);
		i++;
	}
	return (1);
}
