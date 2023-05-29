/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:53:28 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/29 15:46:30 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int		g_global;

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
		if (S_ISREG(path_stat.st_mode) && (path_stat.st_mode & S_IXUSR) == 0)
			return (1);
	}
	return (0);
}

static void	child_end(t_pipe *file, t_pars **pars, t_data *data)
{
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
	free_one_cmd_nofound(pars, file, data);
	exit(1);
}

static void	first_child(t_pipe *file, t_pars **pars, t_data *data)
{
	int	in;
	int	out;

	signal(SIGQUIT, siginthandler_fork);
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
	child_end(file, pars, data);
}

static void	one_built_in(t_pipe *file, t_pars **pars, t_data *data)
{
	int	in;
	int	out;

	in = one_cmd_in(file, pars);
	out = one_cmd_out(file, pars);
	if (in > 0)
		close(in);
	if (in < 0)
	{
		msg(ERR_INFILE, 126);
		return ;
	}
	builtin_exec(pars, data, file);
	if (out > 1)
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
