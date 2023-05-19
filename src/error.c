/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:48:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/18 14:50:28 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
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
	int	i;

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
	//i = -1;
	/*while (file->cmd_args[i++])
		free(file->cmd_args[i]);*/
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
