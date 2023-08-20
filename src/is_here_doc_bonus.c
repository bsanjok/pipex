/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:10:19 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/02 13:13:26 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	is_here_doc(t_pipe *pipex, char *limiter)
{
	int		heredoc;
	char	*str;

	heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc == -1)
	{
		free(pipex);
		ft_printf("pipex: %s: %s\n", strerror(errno), "here_doc");
		exit (127);
	}
	write(1, "pipe heredoc> ", 14);
	str = get_next_line(STDIN_FILENO);
	ft_putstr_fd(str, heredoc);
	while (compare_cmd(str, limiter) != 1)
	{
		free(str);
		write(1, "pipe heredoc> ", 14);
		str = get_next_line(STDIN_FILENO);
		if (compare_cmd(str, limiter) != 1)
		{
			ft_putstr_fd(str, heredoc);
			ft_putstr_fd("\n", heredoc);
		}
	}
	free(str);
}
