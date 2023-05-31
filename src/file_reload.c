/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:20:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 11:50:58 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_files(t_pars **pars, int opening)
{
	while ((*pars) != NULL)
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
}

static void	file_open_one(t_pars **pars)
{
	t_pars	*tmp;
	int		opening;

	tmp = *pars;
	opening = 0;
	open_files(pars, opening);
	*pars = tmp;
	return ;
}

int	only_hdoc_one(t_pars **pars)
{
	t_pars	*tmp;

	tmp = *pars;
	while ((*pars) != NULL)
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
	file_open_one(pars);
	return (0);
}
