/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:29:45 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/24 10:32:11 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	writting_echo(t_pars **pars, t_pipe *file)
{
	int	flag;

	flag = 0;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT
			&& (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		if (ft_strncmp((*pars)->str, "-n", 2) == 0 && flag == 0)
		{
			flag++;
			if ((*pars)->next != NULL)
				(*pars) = (*pars)->next;
		}
		if ((*pars)->str)
		{
			ft_putstr_fd((*pars)->str, file->outfile);
			ft_putstr_fd(" ", file->outfile);
		}
		(*pars) = (*pars)->next;
	}
	if (flag == 0)
		ft_putstr_fd("\n", file->outfile);
	return ;
}

void	ft_echo(t_pars **pars, t_pipe *file)
{
	int	flag;
	int	i;

	flag = 0;
	i = 2;
	if ((*pars)->token == BUILTIN && (*pars)->next == NULL)
		return ;
	if ((*pars)->next != NULL || (*pars)->token == BUILTIN)
		(*pars) = (*pars)->next;
	writting_echo(pars, file);
	return ;
}
