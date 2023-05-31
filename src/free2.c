/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:15:47 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 17:17:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_path(t_pipe *file)
{
	int	i;

	i = -1;
	if (file->cmd_paths)
	{
		while (file->cmd_paths[++i])
			free(file->cmd_paths[i]);
		free(file->cmd_paths);
	}
	i = -1;
	if (file->cmd_to_exec)
	{
		while (file->cmd_to_exec[++i])
			free(file->cmd_to_exec[i]);
	}
}

void	multi_free_no_path(t_pipe *file)
{
	int	i;

	i = -1;
	if (file->cmd_paths)
	{
		while (file->cmd_paths[++i])
			free(file->cmd_paths[i]);
		free(file->cmd_paths);
	}
	i = -1;
	if (file->cmd_to_exec)
	{
		while (file->cmd_to_exec[++i])
			free(file->cmd_to_exec[i]);
	}
	free(file->cmd_to_exec);
	if (file->cmd)
		free(file->cmd);
	if (file->paths)
		free(file->paths);
}
