/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:56:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/06 13:23:38 by luciefer         ###   ########.fr       */
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


static void	new_pipe(t_pipe *file)
{
	int	i;

	i = 0;
	while (i < file->cmd_nb)
	{
		if (pipe(file->pipe + (2 * i)) < 0)
			parent_free(file);
		i++;
	}
}

static void	neww(int infile, int outfile)
{
	dup2(infile, 0);
	dup2(outfile, 1);
}



/*static int many_pipe(t_pars **pars)
{
	t_pars  *tmp;
	int     count;
	
	tmp = *pars;
	count = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
	}
	*pars = tmp;
	return (count);
}*/

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
	while ((*pars) != NULL && ((*pars)->token != PIPE && (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT))
	{
		if ((*pars)->token == CMD)
		{
			if((*pars)->token != CMD && (*pars)->token != R_INPUT)
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

static void	multiple_cmd(t_pipe *file, char **envp, t_pars **pars)
{
	int     i;
	
	i = 0;
	file->pid[file->pidx] = fork();
	if (!file->pid[file->pidx])
	{
		if (file->pidx == 0)
			neww(file->infile, file->pipe[1]);
		else if (file->pidx == file->cmd_nb - 1)
			neww(file->pipe[2 * file->pidx - 2], file->outfile);
		else
			neww(file->pipe[2 * file->pidx - 2], file->pipe[2 * file->pidx + 1]);
		close_pipes(file);
		//file->cmd_args = ft_split(file->cmd_to_exec[file->pidx], ' ');
		file->cmd_args = tema_larg2(file, pars);
		file->cmd = get_cmd(file->cmd_paths, file->cmd_args[0]);
		//printf("CDM to b executed is %s\n", file->cmd);
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
	}
}

void    mult_cmd(t_pipe *file, t_pars **pars, char **envp)
{
	int    i;
	(void)envp;
	
	i = 0;
	redirect_hdoc(pars, file);
	is_heredoc(file, pars);
	file->outfile = 1;
	out_read_v2(file, pars);
	//file->pipe_count = many_pipe(pars);
	file->pipe_nb = pipe_count(pars);
	file->pipe = malloc(sizeof(int *) * file->pipe_nb);
	if (pipe(file->pipe) < 0)
		msg_error(ERR_PIPE, file);
	new_pipe(file);
	//printf("DEBUGGGGG\n");
	file->pid = malloc(sizeof(pid_t) * (file->cmd_nb));
	if (!file->pid)
		pid_err(file);
	//printf("PIDX = %d et CMD_MB = %d\n", file.pidx, file.cmd_nb);
	while (file->pidx < file->cmd_nb)
	{
		multiple_cmd(file, envp, pars);
		file->pidx++;
	}
	close_pipes(file);
	while (i < file->cmd_nb)
	{
		waitpid(file->pid[i], NULL, 0);
		i++;
	}
	parent_free(file);
	free(file->pid);
	return ;
}
