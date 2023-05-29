/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:45:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/29 17:04:51 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_nodess(t_pipe *file)
{
	t_node *node;
	
	while (file->node)
	{
		node = file->node->next;
		close(file->node->fd[0]);
		free(file->node);
		file->node = node;
	}
}

int	find_doc_fd(t_node *head, char *limiter)
{
	t_node	*node;

	node = head;
	while (node)
	{
		if (node->limiter == limiter)
			break ;
		node = node->next;
	}
	return (node->fd[0]);
}

void	init_pipes(t_pipe *file)
{
	t_node	*node;

	node = file->node;
	while (node)
	{
		pipe(node->fd);
		node = node->next;
	}
}

void	close_here_doc_pipe(t_node *head, int read, int write)
{
	t_node	*node;

	node = head;
	while (node)
	{
		if (read)
			close(node->fd[0]);
		if (write)
			close(node->fd[1]);
		node = node->next;
	}
}
