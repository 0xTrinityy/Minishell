/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:53:28 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/21 13:16:16 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_global;

static void parent_free_one(t_pipe *file)
{
	int     i;
	
	i = -1;
	if (file->infile > 0)
		close(file->infile);
	if (file->outfile != 1)
		close(file->outfile);
	while (file->cmd_paths[++i])
		free(file->cmd_paths[i]);
	free(file->cmd_paths);
	i = -1;
	while (file->cmd_to_exec[++i])
		free(file->cmd_to_exec[i]);
	free(file->cmd_to_exec);
	free(file->cmd);
	//printf("gonna free the paths from path spe (file paths) %p\n", file->paths);
	free(file->paths);
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
			if (file->infile != 0 && file->infile > 0)
				close(file->infile);
			file->infile = open((*pars)->next->str, O_RDONLY);
			if (file->infile < 0)
				return (-1);
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
			if (file->outfile != 1)
				close(file->outfile);
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

static int      arg_count(t_pars **pars)
{
	t_pars  *tmp;
	int count;

	tmp = *pars;
	count = 0;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token !=  R_INPUT && (*pars)->token != R_DINPUT))
	{
		count++;
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}

static char    **tema_larg(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int     i;
	char    **arg;
	
	i = arg_count(pars);
	arg = malloc(sizeof(char*) * (i + 1));
	tmp = *pars;
	i = 0;
	arg[i] = (file->cmd_to_exec[0]);
	i++;
	//*pars = (*pars)->next;
	//printf("ELEMENT %s\n", (*pars)->str);
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token !=  R_INPUT && (*pars)->token != R_DINPUT))
	{
		if((*pars)->token != CMD)
		{
			arg[i] = ((*pars)->str);
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
	if (in < 0)
	{
		int i = -1;
		while (data->env[++i])
			free(data->env[i]);
		free(data->env);
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
		msg(ERR_INFILE);
		exit (126);
	}
	out = one_cmd_out(file, pars);
	fprintf(stderr, "OUTFILE = %d\n", out);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	count = 0 ;
	tmp = *pars;
	//printf("PARS STR = %s\n", (*pars)->str);
	if (in > 0)
		close(in);
	if (out != 1)
		close(out);
	//file->paths = find_path_spe(data);
	//file->cmd_paths = ft_split(file->paths, ':');
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
				file->cmd_args[0] = (file->cmd_to_exec[0]);
				//printf("cmd to exec = %s\n", file->cmd_to_exec[0]);
				file->cmd_args[1] = NULL;
			}
			//printf("cmd arg = %s\n", file->cmd_args[1]);
			file->cmd = get_cmd(file->cmd_paths, file->cmd_to_exec[0]);
			break;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if(!file->cmd)
	{
		//parent_free_one(file);
		int i = -1;
		while (data->env[++i])
			free(data->env[i]);
		free(data->env);
		/*while (file->cmd_args[i])
		{
			free(file->cmd_args[i]);
			i++;
		}*/
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
        g_global = 127;
		msg(ERR_CMD);
		exit (127);
	}
	fprintf(stderr, "%s\n", file->cmd_to_exec[0]);
	//printf("cmd arg 2 = %s\n", file->cmd_args[0]);
	//printf("cmd arg 2 = %s\n", file->cmd_args[1]);
	execve(file->cmd, file->cmd_args, data->env);
}

static void    one_built_in(t_pipe *file, t_pars **pars, t_data *data)
{
	int in;
	int out;   

	in = one_cmd_in(file, pars);
	fprintf(stderr, "INFILE = %d\n", in);
	out = one_cmd_out(file, pars);
	fprintf(stderr, "OUTFILE = %d\n", out);
	//dup2(out, STDOUT_FILENO);
	if (in != 0)
		close(in);
	printf("Execution d'un builtin\n");
	builtin_exec(pars, file, data);
	if (out != 1)
		close(out);
	return ;
}


void    one_cmd(t_pipe *file, t_pars **pars, t_data *data)
{	
	int status;

	status = 0;
	file->doc = 0;
	file->outfile = 1;
	file->cmd_args = NULL;
	file->pidx = 0;
	if (file->builtin == 1)
	{
		printf("ON ENTRE BIEN DANS BUILTIN\n");
		one_built_in(file, pars, data);
		parent_free_one(file);
		return ;
	}
	printf("fork()-----------------------------\n");
	printf("ON ENTRE BIEN DANS EXECV");
	file->pidx = fork();
	if (file->pidx == 0)
		first_child(file, pars, data);
	waitpid(file->pidx, &status, 0);
	if (WIFEXITED(status))
        g_global = WEXITSTATUS(status);
	parent_free_one(file);
	return ;
}
