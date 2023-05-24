/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:29:41 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/23 22:32:41 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
