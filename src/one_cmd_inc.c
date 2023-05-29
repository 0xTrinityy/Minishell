/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_inc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:27:06 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/29 14:23:41 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_pars	*find_cmd_pars(t_pars *pars)
{
	while ((pars)->prev != NULL)
		pars = pars->prev;
	while ((pars) != NULL)
	{
		if ((pars)->token == CMD || (pars)->token == BUILTIN)
			return (pars);
		pars = pars->next;
	}
	return (NULL);
}

int	reading_in_one(t_pars **pars, t_pipe *file, int *last, t_pars **cmd)
{
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_INPUT)
		{
			*last = *last + 1;
			*last = *last + 1;
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
			*cmd = find_cmd_pars(*pars);
			*last = HEREDOC;
		}
		(*pars) = (*pars)->next;
	}
	return (0);
}

int	one_cmd_in(t_pipe *file, t_pars **pars)
{
	int		last;
	t_pars	*tmp;
	t_pars	*cmd;

	tmp = *pars;
	cmd = 0;
	last = 0;
	if (last == 0)
		file->infile = STDIN_FILENO;
	if (reading_in_one(pars, file, &last, &cmd) == -1)
	{
		*pars = tmp;
		return (-1);
	}
	*pars = tmp;
	if (last == 0)
		file->infile = STDIN_FILENO;
	else if (last == HEREDOC)
		file->infile = find_doc_fd(file->node, cmd->limiter);
	return (file->infile);
}
