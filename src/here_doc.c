/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:28:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/12 15:37:21 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     find_doc_fd(t_node *head, char *limiter)
{
	t_node  *node;
	
	node = head;
	while (node)
	{
		if (node->limiter == limiter)
			break ;
		node = node->next;
	}
	return (node->fd[0]);
}

void    init_pipes(t_pipe *file)
{
	t_node  *node;
	
	node = file->node;
	while (node)
	{
		/*VERFIER RETOUR FONCTION PIPE TOUT FREE */
		pipe(node->fd);
			/*       */
		node = node->next;
	}
}

void    close_here_doc_pipe(t_node *head, int read, int write)
{
	t_node  *node;
	
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

void handle_write(t_pipe *file)
{
	char    *line;
	t_node  *node;
	
	node = file->node;
	/*CACTH SIGNAL */
	while (node)
	{
		while (1)
		{
			line = readline("heredoc>: ");
			if (line == NULL || ft_strcmp(line, node -> limiter) == 0)
				break ;
			ft_putendl_fd(line, node->fd[1]);
			free(line);
		}
		close(node->fd[0]);
		close(node->fd[1]);
		free(line);
		node = node->next;
	}
	/*FUNCTION POUR TOUT FREE*/
	exit(0);
}

int write_to_pipes(t_pipe *file)
{
	int     status;
	pid_t   pid;
	
	status = 0;
	pid = fork();
	/*if (pid == -1);
		*/
	if (pid == 0)
		handle_write(file);
	else
	{
		close_here_doc_pipe(file->node, 0, 1);
		waitpid(pid, &status, 0);
	}
	/*if (WIFSIGNALED(status) == SIGINT)
		return -1;*/
	return 0;
}

int	here_doc(t_pipe *file)
{
	init_pipes(file);
	return (write_to_pipes(file));
}

