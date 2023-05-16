/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:53:28 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/15 18:50:06 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void parent_free_one(t_pipe *file)
{
	int     i;
	
	i = 0;
	if (file->infile > 0)
		close(file->infile);
	if (file->outfile != 1)
		close(file->outfile);
	//if (file->builtin == 0)
	//{
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	free(file->cmd_to_exec[0]);
	free(file->cmd_to_exec);
	free(file->cmd);
	//}
}

static t_pars* find_cmd_pars(t_pars *pars)
{
	while ((pars) != NULL)
	{
		if ((pars)->token == CMD)
			return pars;
		pars = pars->next;
	}
	return (NULL);
}

static int   one_cmd_in(t_pipe *file, t_pars **pars)
{
	int     last;
	t_pars  *tmp;
	t_pars  *cmd;

	tmp = *pars;
	last = 0;
	
	if (last == 0)
		file->infile = STDIN_FILENO;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_INPUT)
		{
			last++;
			last++;
			file->infile = open((*pars)->next->str, O_RDONLY);
			if (file->infile < 0)
				msg_error(ERR_INFILE, file);
		}
		else if ((*pars)->token == R_DINPUT)
		{
			cmd = find_cmd_pars(*pars);
			last = HEREDOC;
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	if (last == 0)
		file->infile = STDIN_FILENO;
	else if (last == HEREDOC)
	{
		file->infile = find_doc_fd(file->node, cmd->limiter);
		//fprintf( stderr, "HERE DOC INFILE = %d\n", file->infile);
	}
	return (file->infile);
}

static int   one_cmd_out(t_pipe *file, t_pars **pars)
{
	t_pars  *tmp;
	int last;
	
	tmp = *pars;
	last = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_OUTPUT)
			{
				last++;
				file->outfile = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR, 0000644);
				if (file->outfile < 0)
					msg_error(ERR_OUTFILE, file);
			}
			if ((*pars)->token == R_DOUTPUT)
			{
				last++;
				file->outfile = open((*pars)->next->str, O_APPEND | O_CREAT | O_RDWR, 0000644);
				if (file->outfile < 0)
					msg_error(ERR_OUTFILE, file);
			}
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	if (last == 0)
		file->outfile = STDOUT_FILENO;
	return (file->outfile);
}


static char    **tema_larg(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int     i;
	char    **arg;
	
	
	arg = malloc(sizeof(char*) * 100);
	tmp = *pars;
	i = 0;
	arg[i] = file->cmd_to_exec[0];
	i++;
	//*pars = (*pars)->next;
	//printf("ELEMENT %s\n", (*pars)->str);
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token !=  R_INPUT && (*pars)->token != R_DINPUT))
	{
		if((*pars)->token != CMD)
		{
			arg[i] = (*pars)->str;
			//printf("L'arg vaut = %s\n", arg[i]);
			i++;
		}
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	arg[i] = 0;
	return (arg);
}

static void	first_child(t_pipe *file, t_pars **pars, t_data *data)
{
	t_pars *tmp;
	int count;
	int in;
	int out;
	
	
	in = one_cmd_in(file, pars);
	fprintf(stderr, "INFILE = %d\n", in);
	out = one_cmd_out(file, pars);
	fprintf(stderr, "OUTFILE = %d\n", out);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	count = 0 ;
	tmp = *pars;
	//printf("PARS STR = %s\n", (*pars)->str);
	if (in != 0)
		close(in);
	if (out != 1)
		close(out);
	file->paths = find_path_spe(data);
	file->cmd_paths = ft_split(file->paths, ':');
	if (file->builtin != 0)
	{
		printf("DEBUGGG le s\n");
		builtin_exec(pars, file, data);
		return ;
	}
	while (*pars != NULL && ((*pars)->token != R_OUTPUT || (*pars)->token != R_DOUTPUT)) 
	{
		if ((*pars)->token == CMD)
		{
			count = 1;
			if ((*pars)->next != NULL)
				file->cmd_args = tema_larg(pars, file);
			else
			{
				file->cmd_args = malloc(sizeof(char *) * 2);
				file->cmd_args[0] = file->cmd_to_exec[0];
				printf("cmd to exec = %s\n", file->cmd_to_exec[0]);
				file->cmd_args[1] = 0;
			}
			//printf("cmd arg = %s\n", file->cmd_args[1]);
			file->cmd = get_cmd(file->cmd_paths, file->cmd_to_exec[0]);
			break;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if (count == 0 && file->cmd == NULL)
	{
		msg_error(ERR_CMD, file);
	}
	fprintf(stderr, "%s\n", file->cmd_to_exec[0]);
	//printf("cmd arg 2 = %s\n", file->cmd_args[0]);
	//printf("cmd arg 2 = %s\n", file->cmd_args[1]);
	execve(file->cmd, file->cmd_args, data->env);
}

void    one_cmd(t_pipe *file, t_pars **pars, t_data *data)
{	
	file->doc = 0;
	file->outfile = 1;
	file->cmd_args = NULL;
	file->pidx = fork();
	if (file->pidx == 0)
		first_child(file, pars, data);
	waitpid(file->pidx, NULL, 0);
	parent_free_one(file);
	return ;
}
