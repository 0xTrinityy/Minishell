/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:59:26 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/03 11:01:27 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all1(t_pipe *file)
{
	close(file->pipe[0]);
	close(file->pipe[1]);
	close(file->outfile);
	if (file->infile != -1)
		close(file->infile);
	close(4);
	close(5);
	close(6);
}

void	parent_free1(t_pipe *file)
{
	int	i;

	i = 0;
	if (file->infile != -1)
		close(file->infile);
	close(file->outfile);
	while (file->cmd_paths[i])
	{
		free(file->cmd_paths[i]);
		i++;
	}
	free(file->cmd_paths);
	free(file->pipe);
	free(file->pid);
}

void	child_free1(t_pipe *file)
{
	int	i;

	i = 0;
	while (file->cmd_args[i])
	{
		free(file->cmd_args[i]);
		i++;
	}
	free(file->cmd_args);
	free(file->cmd);
}