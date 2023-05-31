/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:00:56 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 10:01:33 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cmdd_cpy(t_pars **pars, t_pipe *file, int index)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((*pars) != NULL && (*pars)->token != PIPE)
	{
		if ((*pars)->token == CMD || (*pars)->token == BUILTIN)
		{
			flag = 1;
			file->cmd_to_exec[index] = ft_strdup((*pars)->str);
		}
		(*pars) = (*pars)->next;
	}
	if (flag == 0)
		file->cmd_to_exec[index] = ft_strdup("\0");
	if ((*pars))
	{
		if ((*pars)->token == PIPE)
			(*pars) = (*pars)->next;
	}
	return ;
}

static int	dupp_counter(t_pars **pars)
{
	t_pars	*tmp;
	int		count;

	tmp = *pars;
	count = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}

void	dup_cmdd(t_pars **pars, t_pipe *file)
{
	t_pars	*tmp;
	int		i;
	int		count;

	tmp = *pars;
	i = 0;
	count = dupp_counter(pars);
	file->cmd_to_exec = malloc(sizeof(char *) * (count + 2));
	if (!file->cmd_to_exec)
		return ;
	while (i < (count + 1))
	{
		cmdd_cpy(pars, file, i);
		i++;
	}
	file->cmd_to_exec[i] = 0;
	*pars = tmp;
}
