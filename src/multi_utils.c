/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:20:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/29 14:35:08 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	neww(int infile, int outfile)
{
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

char	**return_arg(t_pars **pars, t_pipe *file, char **arg, int count)
{
	arg[count] = file->cmd_to_exec[file->pidx];
	count++;
	while ((*pars)->token != CMD)
		(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != PIPE
			&& (*pars)->token != R_INPUT && (*pars)->token != R_DINPUT
			&& (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT))
	{
		if ((*pars)->token != CMD && (*pars)->token != PIPE)
		{
			if ((*pars)->token != CMD && (*pars)->token != R_INPUT
				&& (*pars)->token != PIPE)
			{
				arg[count] = (*pars)->str;
				count++;
			}
			(*pars) = (*pars)->next;
		}
		else
			(*pars) = (*pars)->next;
	}
	arg[count] = 0;
	return (arg);
}

char	**tema_larg2(t_pipe *file, t_pars **pars)
{
	t_pars	*tmp;
	int		count;
	char	**arg;

	count = 0;
	tmp = *pars;
	arg = malloc(sizeof(char *) * 10);
	if (!arg)
		return (NULL);
	while (count != file->pidx && (*pars) != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		(*pars) = (*pars)->next;
	}
	count = 0;
	arg = return_arg(pars, file, arg, count);
	*pars = tmp;
	return (arg);
}
