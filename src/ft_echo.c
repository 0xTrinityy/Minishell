/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:29:45 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/21 13:46:05 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void    ft_echo(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int  flag;
	int  i;
	
	flag = 0;
	i = 2;
	(void)file;	
	tmp = *pars;
	if ((*pars)->next != NULL)
		(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		if (ft_strncmp((*pars)->str, "-n", 2) == 0 && flag == 0)
		{
			flag++;
			if ((*pars)->next != NULL)
				(*pars) = (*pars)->next;
		}
		if ((*pars)->str)
			ft_putstr_fd((*pars)->str, file->outfile);
		(*pars) = (*pars)->next;
	}
	if (flag == 0)
		ft_putstr_fd("\n", file->outfile);
	return ;
}