/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:56:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/08 18:05:16 by tbelleng         ###   ########.fr       */
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

static void	read_doc(t_pipe *file)
{
	int		fd;
	int     size;
	char	*buffer;

	fd = open(".here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0000644);
	if (fd < 0)
		msg_error(ERR_HEREDOC, file);
	size = ft_strlen(file->limit);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, file->limit, size))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	file->infile = open(".here_doc", O_RDONLY);
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

static int    redirect_in(t_pipe *file, t_pars **pars)
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
			if ((*pars)->token == R_INPUT || (*pars)->token == R_DINPUT)
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
			if ((*pars)->token == R_INPUT)
			{
				file->infile = open((*pars)->next->str, O_RDONLY);
				if (file->infile < 0)
					msg_error(ERR_INFILE, file);
			}
			if ((*pars)->token == R_DINPUT)
			{
				read_doc(file);
				if (file->infile < 0)
					msg_error(ERR_INFILE, file);
				file->doc = 1;
			}
		(*pars) = (*pars)->next;
		}
	}
	else
	{
		if (file->pidx == 0)
			file->infile = 0;
		else
			file->infile = file->pipe[2 * file->pidx - 2];
	}
	*pars = tmp;
	return (file->outfile);
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
		if (file->pidx == 0)
			file->outfile = file->pipe[1];
		else if (file->pidx == file->cmd_nb - 1)
			file->outfile = 1;
		else
			file->outfile = file->pipe[2 * file->pidx + 1];
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
		out = redirect_out(file, pars);
		//printf("la valeur de l'out vaut %d\n", out);
		if (file->pidx == 0)
			neww(in, out);
		else if (file->pidx == file->cmd_nb - 1)
			neww(in, out);
		else
			neww(in, out);
		close_pipes(file);
		//file->cmd_args = ft_split(file->cmd_to_exec[file->pidx], ' ');
		file->cmd_args = tema_larg2(file, pars);
		file->cmd = get_cmd(file->cmd_paths, file->cmd_args[0]);
		//printf("ARG to b executed is %s\n", file->cmd_args[1]);
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
	//redirect_hdoc(pars, file);
	//is_heredoc(file, pars);
	file->infile = 0;
	file->outfile = 1;
	file->pidx = 0;
	file->doc = 0;
	file->out_nb = 0;
	//out_read_v2(file, pars);
	file->pipe_nb = pipe_count(pars);
	file->pipe = malloc(sizeof(int *) * file->pipe_nb);
	if (pipe(file->pipe) < 0)
		msg_error(ERR_PIPE, file);
	new_pipe(file);
	//printf("INFILE = %d\n", file->infile);
	file->pid = malloc(sizeof(pid_t) * (file->cmd_nb));
	if (!file->pid)
		pid_err(file);
	//printf("PIDX = %d et CMD_MB = %d\n", file->pidx, file->cmd_nb);
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
	/*while (file->out_nb > 0)
	{
		close(file->out_fd[file->out_nb - 1]);
		file->out_nb--;
	}*/
	//free(file->out_fd);
	free(file->pid);
	return ;
}
