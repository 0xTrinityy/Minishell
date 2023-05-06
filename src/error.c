/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:48:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/06 13:23:41 by luciefer         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < (file->pipe_nb))
	{
		close(file->pipe[i]);
		i++;
	}
	free(file->pipe);
}

void	parent_free(t_pipe *file)
{
	int	i;

	i = 0;
	if (file->infile != -1 && file->infile != 0)
		close(file->infile);
	if (file->outfile != 1)
		close(file->outfile);
	if (file->doc == 1 && unlink(".here_doc") == -1)
		msg_error(ERR_UNLINK, file);
	while (file->cmd_paths[i])
	{
		free(file->cmd_paths[i]);
		i++;
	}
	free(file->cmd_paths);
	i = 0;
	while(file->cmd_to_exec[i])
	{
		free(file->cmd_to_exec[i]);
		i++;
	}
	free(file->cmd_to_exec);
	free(file->cmd);
	//free(file->pipe);
	close(6);
	close(5);
	close(4);
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
