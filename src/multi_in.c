/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:33:59 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/29 14:31:36 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_pars	*find_cmd_pars(t_pars *pars)
{
	while ((pars)->prev != NULL && (pars)->token != PIPE)
		pars = pars->prev;
	pars = pars->next;
	while ((pars) != NULL && pars->token != PIPE)
	{
		if ((pars)->token == CMD || (pars)->token == BUILTIN)
			return (pars);
		pars = pars->next;
	}
	return (NULL);
}

void	redirect_infirst(t_pars **pars, t_pipe *file, int *last, t_pars *cmd)
{
	int	nb_rd;

	nb_rd = 0;
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token == R_INPUT)
		{
			if (file->infile > 0)
				close(file->infile);
			*last = INFILE;
			file->infile = open((*pars)->next->str, O_RDONLY);
			if (file->infile < 0)
				return ;
			nb_rd++;
		}
		else if ((*pars)->token == R_DINPUT)
			*last = HEREDOC;
		(*pars) = (*pars)->next;
	}
	if (nb_rd == 0)
		file->infile = 0;
	if (*last == HEREDOC)
		file->infile = find_doc_fd(file->node, cmd->limiter);
}

int	pass_pipe(t_pars **pars, t_pipe *file)
{
	int	count;

	count = 0;
	while (count != file->pidx && (*pars) != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		(*pars) = (*pars)->next;
	}
	return (count);
}

void	redirect_in2(t_pars **pars, t_pipe *file, int *last, t_pars *cmd)
{
	int	nb_rd;

	nb_rd = 0;
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token == R_INPUT)
		{
			if (file->infile > 0)
				close(file->infile);
			*last = INFILE;
			file->infile = open((*pars)->next->str, O_RDONLY);
			if (file->infile < 0)
				return ;
			nb_rd++;
		}
		else if ((*pars)->token == R_DINPUT)
		{
			if (file->infile > 0)
				close(file->infile);
			*last = HEREDOC;
			nb_rd++;
		}
		(*pars) = (*pars)->next;
	}
	redirect_output(file, last, nb_rd, cmd);
}

int	redirect_in(t_pipe *file, t_pars **pars)
{
	int		count;
	int		nb_rd;
	t_pars	*tmp;
	t_pars	*cmd;
	int		last;

	count = 0;
	nb_rd = 0;
	tmp = *pars;
	last = -1;
	if (file->pidx == 0)
	{
		cmd = find_cmd_pars(*pars);
		redirect_infirst(pars, file, &last, cmd);
		*pars = tmp;
		return (file->infile);
	}
	else
	{
		count = pass_pipe(pars, file);
		cmd = find_cmd_pars(*pars);
		redirect_in2(pars, file, &last, cmd);
		*pars = tmp;
		return (file->infile);
	}
}
