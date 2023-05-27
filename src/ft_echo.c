/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:29:45 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/27 16:11:14 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_option(t_pars **pars)
{
	int	i;
	int	j;

	j = 0;
	while (*pars != NULL && (*pars)->str[0] == '-' && (*pars)->str[1] == 'n')
	{
		i = 2;
		while ((*pars)->str[i] && (*pars)->str[i] == 'n')
			i++;
		if ((*pars)->str[i] && (*pars)->str[i] != 'n')
			break ;
		j++;
		*pars = (*pars)->next;
	}
	if (j > 0)
		return (1);
	else
		return (0);
}

static void	writting_echo(t_pars *pars, int flag)
{
	while (pars != NULL && (pars->token != R_OUTPUT && pars->token != R_DOUTPUT
			&& pars->token != PIPE))
	{
		if (pars->str)
			printf("%s", pars->str);
		if (pars->str[0] && pars->next != NULL)
			printf(" ");
		pars = pars->next;
	}
	if (flag == 0)
		printf("\n");
	return ;
}

void	ft_echo(t_pars **pars)
{
	t_pars	*tmp;
	int		i;

	tmp = *pars;
	if ((*pars)->token == BUILTIN && (*pars)->next == NULL)
		printf("\n");
	else if ((*pars)->token == BUILTIN)
	{
		(*pars) = (*pars)->next;
		i = check_option(pars);
		writting_echo(*pars, i);
	}
	*pars = tmp;
	return ;
}
