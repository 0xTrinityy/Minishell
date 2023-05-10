/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:56:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/10 19:35:10 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//L'OFFICIEL

/*char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths != NULL)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}*/

void create_node_and_list(t_pipe *file, char *limiter)
{
	t_node  *node;
	
	node = ft_calloc(sizeof(t_node), 1);
	//if (node == NULL)
		/*exit function*/
	node -> limiter = limiter;
	if (file->node == NULL)
	{
		file->node = node;
		file->last = node;
	}
	else
	{
		file->last->next = node;
		node->prev = file->last;
		file->last = node;
	}
}


static int    pipe_count(t_pars **pars)
{
	int     count;
	t_pars  *tmp;
	
	count = 0;
	tmp = *pars;
	while(*pars != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		*pars = (*pars)->next;
	}
	*pars = tmp;
	count = count * 2;
	return (count);
}



static void	neww(int infile, int outfile)
{
	dup2(infile, STDIN_FILENO);
	close(infile);
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

static char **tema_larg2(t_pipe *file, t_pars **pars)
{
	t_pars  *tmp;
	int     count;
	char    **arg;
	
	count = 0;
	tmp = *pars;
	arg = malloc(sizeof(char *) * 20000);
	while (count != file->pidx && (*pars) != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		(*pars) = (*pars)->next;
	}
	count = 0;
	arg[count] = file->cmd_to_exec[file->pidx];
	count++;
	while ((*pars)->token != CMD)
			(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != PIPE && (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT))
	{
		if ((*pars)->token != CMD && (*pars)->token != PIPE)
		{
			if((*pars)->token != CMD && (*pars)->token != R_INPUT && (*pars)->token != PIPE)
			{
				arg[count] = (*pars)->str;
				//printf("L'arg vaut = %s\n", arg[count]);
				count++;
			}
			(*pars) = (*pars)->next;
		}
		else
			(*pars) = (*pars)->next;
	}
	arg[count] = 0;
	*pars = tmp;
	return (arg);
}

static t_pars* find_cmd_pars(t_pars *pars)
{
	while ((pars) != NULL && pars->token != PIPE)
	{
		if ((pars)->token == CMD)
			return pars;
		pars = pars->next;
	}
	return (NULL);
}

static int    redirect_in(t_pipe *file, t_pars **pars)
{
	int     count;
	int     nb_rd;
	t_pars  *tmp;
	t_pars  *cmd;
	int     last;
	
	count = 0;
	nb_rd = 0;
	tmp = *pars;
	last = -1;
	//printf("entering infile\n");
	if (file->pidx == 0)
	{
		cmd = find_cmd_pars(*pars);
		while ((*pars) != NULL && (*pars)->token != PIPE)
		{
			if ((*pars)->token == R_INPUT)
			{
				last = INFILE;
				file->infile = open((*pars)->next->str, O_RDONLY);
				if (file->infile < 0)
					msg_error(ERR_INFILE, file);
				nb_rd++;
			}
			else if ((*pars)->token == R_DINPUT)
				last = HEREDOC;
			(*pars) = (*pars)->next;
		}
		*pars = tmp;	
		if (nb_rd == 0)
			file->infile = 0;
		if (last == HEREDOC)
			file->infile = find_doc_fd(file->node, cmd->limiter);
		return (file->infile);
	}
	else
	{
		while (count != file->pidx && (*pars) != NULL)
		{
			if ((*pars)->token == PIPE)
				count++;
			(*pars) = (*pars)->next;
		}
		cmd = find_cmd_pars(*pars);
		while ((*pars) != NULL && (*pars)->token != PIPE)
		{
			if ((*pars)->token == R_INPUT)
			{
				last = INFILE;
				file->infile = open((*pars)->next->str, O_RDONLY);
				if (file->infile < 0)
					msg_error(ERR_INFILE, file);
				nb_rd++;
			}
			else if ((*pars)->token == R_DINPUT)
			{
				last = HEREDOC;
				nb_rd++;
			}
			(*pars) = (*pars)->next;
		}
		*pars = tmp;
		if (nb_rd == 0)
			file->infile = file->fd[0];
		if (last == HEREDOC)
			file->infile = find_doc_fd(file->node, cmd->limiter);
		return (file->infile);
	}
}

static int    redirect_out(t_pipe *file, t_pars **pars)
{
	int     count;
	t_pars  *tmp;
	
	count = 0;
	tmp = *pars;
	
	if (file->pidx != 0)
	{
		while (count != file->pidx && (*pars) != NULL)
		{
			if ((*pars)->token == PIPE)
				count++;
			(*pars) = (*pars)->next;
		}
	}
	else if (file->pidx == 0)
	{
		while ((*pars)->token != PIPE)
		{
			if ((*pars)->token == R_OUTPUT || (*pars)->token == R_DOUTPUT)
				count++;
			(*pars) = (*pars)->next;
		}
		*pars = tmp;
	}
	//printf("LE COUNT = %d\n", count);
	if (count != 0)
	{
		while ((*pars) != NULL && (*pars)->token != PIPE)
		{
			if ((*pars)->token == R_OUTPUT)
			{
				file->outfile = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR, 0000644);
				if (file->outfile < 0)
					msg_error(ERR_OUTFILE, file);
			}
			if ((*pars)->token == R_DOUTPUT)
			{
				file->outfile = open((*pars)->next->str, O_APPEND | O_CREAT | O_RDWR, 0000644);
				if (file->outfile < 0)
					msg_error(ERR_OUTFILE, file);
			}
			(*pars) = (*pars)->next;
		}
	}
	else
	{
		if (file->pidx == file->cmd_nb - 1)
			file->outfile = STDOUT_FILENO;
		else
			file->outfile = file->fd[1];
	}
	*pars = tmp;
	return (file->outfile);
}


static void	multiple_cmd(t_pipe *file, char **envp, t_pars **pars)
{
	int     i;
	int     in;
	int     out;
	
	i = 0;
	file->pid[file->pidx] = fork();
	if (!file->pid[file->pidx])
	{
		in = redirect_in(file, pars);
		printf("INFILE = %d\n", in);
		out = redirect_out(file, pars);
		printf("OUTFILE = %d\n", out);
		neww(in, out);
		close_pipes(file);
		fprintf(stderr, "%s\n", file->cmd_to_exec[file->pidx]);
		file->cmd_args = tema_larg2(file, pars);
		file->cmd = get_cmd(file->cmd_paths, file->cmd_args[0]);
		/*fprintf(stderr, "ARG to b executed is %s\n", file->cmd_args[0]);
		fprintf(stderr, "ARG to b executed is %s\n", file->cmd_args[1]);*/
		if (!file->cmd)
		{
			child_free1(file);
			close_all1(file);
			parent_free1(file);
			msg(ERR_CMD);
			exit(1);
		}
		execve(file->cmd, file->cmd_args, envp);
		printf("EXEC FAIL\n");
		error_free(file);
		free(file->cmd);
		exit(1);
	}
}

void    mult_cmd(t_pipe *file, t_pars **pars, char **envp)
{
	int    i;
	(void)envp;
	
	i = -1;
	file->outfile = 1;
	file->prev_pipes = -1;
	file->pipe_nb = pipe_count(pars);
	file->pid = malloc(sizeof(pid_t) * (file->cmd_nb));
	if (!file->pid)
		pid_err(file);
	while (file->pidx < file->cmd_nb)
	{
		if (file->pidx != file->cmd_nb - 1 && pipe(file->fd) < 0)
			msg_error(ERR_PIPE, file);
		multiple_cmd(file, envp, pars);
		close(file->fd[1]);
		if (file->prev_pipes != -1)
			close(file->prev_pipes);
		file->prev_pipes = file->fd[0];
		file->pidx++;
	}
	close_here_doc_pipe(file->node, 1, 0);
	while (++i < file->cmd_nb)
		waitpid(file->pid[i], NULL, 0);
	parent_free(file);
	return ;
}
