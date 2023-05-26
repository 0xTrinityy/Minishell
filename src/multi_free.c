/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:32:21 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 13:46:34 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pars(t_pars **pars)
{
	t_pars	*tmp;

	while ((*pars) != NULL)
	{
		tmp = (*pars)->next;
		free((*pars)->id);
		free((*pars)->str);
		free(*pars);
		*pars = tmp;
	}
}

void	free_in(t_pars **pars, t_pipe *file, t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		free(data->env[i]);
	free(data->env);
	i = -1;
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	i = -1;
	while (file->cmd_to_exec[++i])
		free(file->cmd_to_exec[i]);
	free(file->cmd_to_exec);
	free(file->cmd);
	free(file->paths);
	free(file->pid);
	free_pars(pars);
}

void	free_builtin(t_pars **pars, t_pipe *file, t_data *data)
{
	int		i;
	t_node	*tmp1;

	i = -1;
	while (data->env[++i])
		free(data->env[i]);
	free(data->env);
	i = -1;
	while (file->cmd_to_exec[++i])
		free(file->cmd_to_exec[i]);
	free(file->cmd_to_exec);
	i = -1;
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	free(file->paths);
	free(file->pid);
	while (file->node)
	{
		tmp1 = file->node->next;
		free(file->node);
		file->node = tmp1;
	}
	free_pars(pars);
}

static void	free_node(t_pipe *file)
{
	t_node	*tmp1;

	while (file->node)
	{
		tmp1 = file->node->next;
		free(file->node);
		file->node = tmp1;
	}
}

void	free_no_cmd(t_pars **pars, t_pipe *file, t_data *data)
{
	int		i;

	i = -1;
	while (data->env[++i])
		free(data->env[i]);
	free(data->env);
	free(file->cmd_args);
	i = -1;
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	i = -1;
	while (file->cmd_to_exec[++i])
		free(file->cmd_to_exec[i]);
	free(file->cmd_to_exec);
	free(file->cmd);
	free(file->paths);
	free(file->pid);
	free_node(file);
	free_pars(pars);
}
