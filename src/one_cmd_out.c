/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:27:17 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/28 16:36:55 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reading_out(t_pars **pars, t_pipe *file, int last)
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

int	one_cmd_out(t_pipe *file, t_pars **pars)
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
