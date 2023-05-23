/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:27:15 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/23 17:03:25 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	only_error(char *err)
{
	perror(err);
}

int    only_file(t_pars **pars)
{
	t_pars  *tmp;
	
	tmp = *pars;
	while ((*pars) != NULL)
	{
		if ((*pars)->token != R_INPUT && (*pars)->token != R_DINPUT && (*pars)->token != R_OUTPUT &&
				(*pars)->token != R_DOUTPUT && (*pars)->token != ARG  && (*pars)->token != PIPE)
		{
			*pars = tmp;
			return (0);
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return (1);
}

void    only_file_handler(t_pars **pars)
{
	t_pars  *tmp;
	int     opening;
	
	tmp = *pars;
	opening = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_INPUT)
		{
			opening = open((*pars)->next->str, O_RDONLY);
			if (opening < 0)
			{
				only_error(ERR_INFILE);
				break;
			}
			close(opening);
		}
		if ((*pars)->token == R_OUTPUT || (*pars)->token == R_DOUTPUT)
		{
			opening = open((*pars)->next->str, O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if (opening < 0)
			{
				only_error(ERR_OUTFILE);
				break;
			}
			printf("gonna close : %d\n", opening);
			close(opening);
		}
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return ;
}