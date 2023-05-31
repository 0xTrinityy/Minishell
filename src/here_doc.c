/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:28:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 17:16:19 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_heredoc(t_pars **pars, t_pipe *file)
{
	t_node	*node;

	while (file->node)
	{
		node = file->node->next;
		free(file->node);
		file->node = node;
	}
	free(file->cmd_args);
	here_doc_path(file);
	free(file->cmd_to_exec);
	if (file->cmd)
		free(file->cmd);
	if (file->paths)
		free(file->paths);
	free_pars(pars);
	return ;
}

static void	free_env_hdoc(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		free(data->env[i]);
	free(data->env);
}

void	handle_write(t_pipe *file, t_pars **pars, t_data *data)
{
	char	*line;
	t_node	*node;

	node = file->node;
	while (node)
	{
		while (1)
		{
			line = readline("heredoc>: ");
			if (line == NULL || ft_strcmp(line, node->limiter) == 0)
				break ;
			ft_putendl_fd(line, node->fd[1]);
			free(line);
		}
		close(node->fd[0]);
		close(node->fd[1]);
		free(line);
		node = node->next;
	}
	free_env_hdoc(data);
	free_heredoc(pars, file);
	exit(0);
}

int	write_to_pipes(t_pipe *file, t_pars **pars, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		handle_write(file, pars, data);
	else
	{
		close_here_doc_pipe(file->node, 0, 1);
		waitpid(pid, &status, 0);
	}
	return (0);
}

int	here_doc(t_pipe *file, t_pars **pars, t_data *data)
{
	init_pipes(file);
	return (write_to_pipes(file, pars, data));
}
