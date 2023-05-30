/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:39:50 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 17:15:27 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_builtin_exit(t_pars **pars, t_pipe *file, t_data *data)
{
	while ((*pars)->prev != NULL)
		(*pars) = (*pars)->prev;
	free_builtin(pars, file, data);
}

static void	exit_endmult(t_pars **pars, t_pipe *file, t_data *data, t_pars *tmp)
{
	long long int	i;

	i = 0;
	(*pars) = (*pars)->next;
	while ((*pars)->str[i])
	{
		if (!ft_isdigit_special((*pars)->str[i]))
		{
			error_message_exit((*pars)->str);
			*pars = tmp;
			free_builtin_exit(pars, file, data);
			exit(2);
		}
		i++;
	}
	i = ft_atoull((*pars)->str);
	*pars = tmp;
	free_builtin_exit(pars, file, data);
	exit(i);
}

void	ft_exit_built_mult(t_pars **pars, t_pipe *file, t_data *data)
{
	t_pars	*tmp;

	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	if ((*pars)->next == NULL)
	{
		*pars = tmp;
		free_builtin_exit(pars, file, data);
		exit(0);
	}
	if ((*pars)->next->next != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit_endmult(pars, file, data, tmp);
}
