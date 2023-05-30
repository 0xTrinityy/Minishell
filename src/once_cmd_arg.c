/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   once_cmd_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:30:48 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/28 16:34:14 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	arg_count(t_pars **pars)
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

char	**tema_larg(t_pars **pars, t_pipe *file)
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

void	getting_args(t_pars **pars, t_pipe *file)
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
