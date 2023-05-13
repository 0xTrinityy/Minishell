/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:29:45 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 07:20:52 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void    ft_echo(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int  flag;
	
	flag = 0;
	
	(void)file;
	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	if ((*pars)->next != NULL)
		(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		if (ft_strncmp((*pars)->str, "-n", 2) == 0 && flag == 0)
		{
			flag++;
			(*pars) = (*pars)->next;
		}
		printf("%s ", (*pars)->str);
		(*pars) = (*pars)->next;
	}
	if (flag == 0)
		printf("\n");
	*pars = tmp;
	return ;
}