/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:42:04 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 13:30:24 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipe	*pipex;

	if (argc != 5 || !argv[2] || !argv[3])
		return (ft_putstr_fd("Invalid arguments!\n", 2), 2);
	pipex = malloc(sizeof(t_pipe));
	if (!pipex)
		return (-1);
	pipex->has_here_doc = 0;
	pipex->args = argc;
	pipex->commands = argc - 3;
	pipex->path = get_final_path(env);
	if (!pipex->path)
		return (free(pipex), -1);
	init_cmd_bin(pipex, argv);
	init_children(pipex, env, argv);
	free_and_exit(pipex);
	return (0);
}
