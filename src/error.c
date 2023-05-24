/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:48:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/24 18:39:35 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

int	msg(char *err, int i)
{
	write(2, err, ft_strlen(err));
	g_global = i;
	return (1);
}

void	msg_error(char *err, t_pipe *file)
{
	perror(err);
	if (file->infile != -1 && file->infile != 0)
		close(file->infile);
}

void	close_pipes(t_pipe *file)
{
	close_here_doc_pipe(file->node, 1, 0);
	close(file->fd[0]);
	close(file->fd[1]);
	if (file->prev_pipes != -1)
		close(file->prev_pipes);
}

void	parent_free(t_pipe *file)
{
	int		i;
	t_node	*tmp;

	i = -1;
	if (file->infile > 0)
		close(file->infile);
	if (file->outfile != 1)
		close(file->outfile);
	while (file->cmd_paths[++i])
	{
		//printf("gonna free this adress %p\n", file->cmd_paths[i]);
		free(file->cmd_paths[i]);
	}
	free(file->cmd_args);
	free(file->cmd_paths);
	while (file->node)
	{
		tmp = file->node->next;
		free(file->node);
		file->node = tmp;
	}
	i = -1;
	while (file->cmd_to_exec[++i])
	{
		//printf("gonna free this adress %p\n", file->cmd_to_exec[i]);
		free(file->cmd_to_exec[i]);
	}
	free(file->cmd_to_exec);
	free(file->cmd);
	free(file->paths);
	free(file->pid);
}

void	pid_err(t_pipe *file)
{
	parent_free(file);
}

void	infile_error(char *err, t_pipe *file)
{
	perror(err);
	file->infile = -1;
}

void	error_free(t_pipe *file)
{
	int	i;

	i = 0;
	while (file->cmd_args[i] != NULL)
	{
		free(file->cmd_args[i]);
		i++;
	}
	free(file->cmd_args);
}
