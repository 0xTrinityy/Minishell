/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:53:28 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/28 11:52:56 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int		g_global;

static t_pars	*find_cmd_pars(t_pars *pars)
{
	while ((pars) != NULL)
	{
		if ((pars)->token == CMD || (pars)->token == BUILTIN)
			return (pars);
		pars = pars->next;
	}
	return (NULL);
}

static int	one_cmd_in(t_pipe *file, t_pars **pars)
{
	int		last;
	t_pars	*tmp;
	t_pars	*cmd;

	tmp = *pars;
	last = 0;
	if (last == 0)
		file->infile = STDIN_FILENO;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_INPUT)
		{
			last ++;
			last ++;
			if (file->infile != 0 && file->infile > 0)
				close(file->infile);
			file->infile = open((*pars)->next->str, O_RDONLY);
			if (file->infile < 0)
				return (-1);
		}
		else if ((*pars)->token == R_DINPUT)
		{
			if (file->infile > 0)
				close(file->infile);
			cmd = find_cmd_pars(*pars);
			last = HEREDOC;
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	if (last == 0)
		file->infile = STDIN_FILENO;
	else if (last == HEREDOC)
		file->infile = find_doc_fd(file->node, cmd->limiter);
	return (file->infile);
}

static int	reading_out(t_pars **pars, t_pipe *file, int last)
{
	t_pars	*tmp;

	tmp = *pars;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_OUTPUT)
		{
			last++;
			if (file->outfile != 1)
				close(file->outfile);
			file->outfile = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR,
					0000644);
			if (file->outfile < 0)
				msg_error(ERR_OUTFILE, file);
		}
		if ((*pars)->token == R_DOUTPUT)
			creating_append(pars, file, &last);
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	return (last);
}

static int	one_cmd_out(t_pipe *file, t_pars **pars)
{
	t_pars	*tmp;
	int		last;

	tmp = *pars;
	last = 0;
	last = reading_out(pars, file, last);
	if (last == 0)
		file->outfile = STDOUT_FILENO;
	return (file->outfile);
}

static int	arg_count(t_pars **pars)
{
	t_pars	*tmp;
	int		count;

	tmp = *pars;
	count = 0;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT
			&& (*pars)->token != R_DOUTPUT && (*pars)->token != R_INPUT
			&& (*pars)->token != R_DINPUT))
	{
		count++;
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}

static char	**tema_larg(t_pars **pars, t_pipe *file)
{
	t_pars	*tmp;
	int		i;
	char	**arg;

	i = arg_count(pars);
	arg = malloc(sizeof(char *) * (i + 1));
	tmp = *pars;
	i = 0;
	arg[i] = (file->cmd_to_exec[0]);
	i++;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT
			&& (*pars)->token != R_DOUTPUT && (*pars)->token != R_INPUT
			&& (*pars)->token != R_DINPUT))
	{
		if ((*pars)->token != CMD)
		{
			arg[i] = ((*pars)->str);
			i++;
		}
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	arg[i] = 0;
	return (arg);
}

static void	getting_args(t_pars **pars, t_pipe *file)
{
	t_pars	*tmp;
	int		count;

	tmp = *pars;
	count = 0;
	while (*pars != NULL)
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
				file->cmd_args[1] = NULL;
			}
			file->cmd = get_cmd(file->cmd_paths, file->cmd_to_exec[0]);
			break ;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
}

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
	}
	return (0);
}

static void	first_child(t_pipe *file, t_pars **pars, t_data *data)
{
	int	in;
	int	out;

	signal(SIGQUIT,siginthandler_fork);
	in = one_cmd_in(file, pars);
	if (in < 0)
	{
		free_one_cmd_infile(pars, file, data);
		msg(ERR_INFILE, 126);
		exit(126);
	}
	out = one_cmd_out(file, pars);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	if (in > 0)
		close(in);
	if (out != 1)
		close(out);
	getting_args(pars, file);
	if (is_regular_file(file->cmd_to_exec[0]))
	{
		free_one_cmd_isfile(pars, file, data);
		msg(ERR_CMD, 127);
		exit(127);
	}
	if (!file->cmd)
	{
		free_one_cmd_nofound(pars, file, data);
		msg(ERR_CMD, 127);
		exit(127);
	}
	execve(file->cmd, file->cmd_args, data->env);
	exit(1);
}

static void	one_built_in(t_pipe *file, t_pars **pars, t_data *data)
{
	int	in;
	int	out;

	in = one_cmd_in(file, pars);
	out = one_cmd_out(file, pars);
	if (in != 0)
		close(in);
	builtin_exec(pars, data, file);
    if (out != 1)
		close(out);
	return ;
}

void	one_cmd(t_pipe *file, t_pars **pars, t_data *data)
{
	int	status;

	status = 0;
	file->doc = 0;
	file->outfile = 1;
	file->cmd_args = NULL;
	file->pidx = 0;
	if (file->builtin == 1)
	{
		one_built_in(file, pars, data);
		parent_free_one(file);
		return ;
	}
	file->pidx = fork();
	if (file->pidx == 0)
		first_child(file, pars, data);
	waitpid(file->pidx, &status, 0);
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	if (WIFEXITED(status))
		g_global = WEXITSTATUS(status);
	close_here_doc_pipe(file->node, 1, 0);
	parent_free_one(file);
	return ;
}
