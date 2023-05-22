/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:28:18 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/22 15:34:07 by tbelleng         ###   ########.fr       */
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

void handle_write(t_pipe *file, t_pars **pars, t_data *data)
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
	int i = -1;
	while (data->env[++i])
		free(data->env[i]);
	free(data->env);
		/*while (file->cmd_args[i])
		{
			free(file->cmd_args[i]);
			i++;
		}*/
	free(file->node->prev);
	free(file->node);
	free(file->cmd_args);
	i = -1;
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	i = -1;
	while(file->cmd_to_exec[++i])
		free(file->cmd_to_exec[i]);
	free(file->cmd_to_exec);
	free(file->cmd);
	free(file->paths);
	t_pars *tmp;
	while ((*pars) != NULL)
	{
		tmp = (*pars)->next;
		free((*pars)->ID);
		free((*pars)->str);
		free(*pars);
		*pars = tmp;
	}
	exit(0);
}

int write_to_pipes(t_pipe *file, t_pars **pars, t_data *data)
{
	int     status;
	pid_t   pid;
	
	status = 0;
	pid = fork();
printf("fork()-----------------------------\n");
	/*if (pid == -1);
		*/
	if (pid == 0)
		handle_write(file, pars, data);
	else
	{
		close_here_doc_pipe(file->node, 0, 1);
		waitpid(pid, &status, 0);
	}
	if (WIFSIGNALED(status) == SIGINT)
		return -1;
	return 0;
}

int	here_doc(t_pipe *file, t_pars **pars, t_data *data)
{
	init_pipes(file);
	return (write_to_pipes(file, pars, data));
}

