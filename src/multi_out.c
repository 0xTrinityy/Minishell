/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:34:04 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/25 16:21:37 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	out_count(t_pars **pars, t_pipe *file, t_pars *tmp)
{
	int	count;

	count = 0;
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
	return (count);
}

void	out_open(t_pars **pars, t_pipe *file)
{
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token == R_OUTPUT)
		{
			if (file->outfile > 1)
				close(file->outfile);
			file->outfile = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR,
					0000644);
			if (file->outfile < 0)
				msg_error(ERR_OUTFILE, file);
		}
		if ((*pars)->token == R_DOUTPUT)
		{
			if (file->outfile > 1)
				close(file->outfile);
			file->outfile = open((*pars)->next->str,
					O_APPEND | O_CREAT | O_RDWR, 0000644);
			if (file->outfile < 0)
				msg_error(ERR_OUTFILE, file);
		}
		(*pars) = (*pars)->next;
	}
}

int	redirect_out(t_pipe *file, t_pars **pars)
{
	int		count;
	t_pars	*tmp;

	tmp = *pars;
	count = out_count(pars, file, tmp);
	if (file->pidx == file->cmd_nb - 1)
		file->outfile = STDOUT_FILENO;
	else
		file->outfile = file->fd[1];
	if (count != 0)
		out_open(pars, file);
	*pars = tmp;
	return (file->outfile);
}
