/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reload_mult.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:02:36 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 10:02:49 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	file_open_mult(t_pars **pars)
{
	t_pars	*tmp;
	int		opening;

	tmp = *pars;
	opening = 0;
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token == R_INPUT)
		{
			opening = open((*pars)->next->str, O_RDONLY);
			if (opening < 0)
			{
				msg(ERR_INFILE, 126);
				break ;
			}
			close(opening);
		}
		else if ((*pars)->token == R_OUTPUT || (*pars)->token == R_DOUTPUT)
		{
			opening = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR,
					0000644);
			if (opening < 0)
			{
				msg(ERR_OUTFILE, 126);
				break ;
			}
			close(opening);
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return ;
}

static void	skip_pipe(t_pars **pars, t_pipe *file)
{
	int	count;

	count = 0;
	while (count != file->pidx)
	{
		if ((*pars)->token == PIPE)
			count++;
		(*pars) = (*pars)->next;
	}
	return ;
}

int	only_hdoc_mult(t_pars **pars, t_pipe *file)
{
	t_pars *tmp;
	int flag;

	tmp = *pars;
	flag = 0;
	skip_pipe(pars, file);
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token != R_INPUT && (*pars)->token != R_DINPUT
			&& (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT
			&& (*pars)->token != ARG)
		{
			*pars = tmp;
			return (1);
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	skip_pipe(pars, file);
	file_open_mult(pars);
	*pars = tmp;
	return (0);
}