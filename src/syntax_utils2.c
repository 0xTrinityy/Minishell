/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:39:26 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:16:06 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_arg(t_pars *pars)
{
	t_pars	*tmp;
	int		i;

	i = 0;
	tmp = pars;
	while (pars != NULL)
	{
		if (i == 2)
			break ;
		if (pars->token == ARG)
		{
			i = 2;
			pars = pars->next;
		}
		if (pars != NULL && pars->token == PIPE)
			return (1);
		if (pars != NULL && is_redirect(pars->token))
		{
			i = 0;
			pars = pars->next;
		}
	}
	if (pars == NULL)
		i = 1;
	pars = tmp;
	if (i == 1)
		return (1);
	return (0);
}

int	check_syntax_redirect(t_pars *pars)
{
	t_pars	*tmp;

	tmp = pars;
	if (pars->token == CMD)
	{
		pars = pars->next;
		while (!is_redirect(pars->token))
			pars = pars->next;
		if (!is_redirect(pars->token))
			return (0);
		pars = pars->next;
		if (!is_arg(pars))
			return (0);
	}
	else if (is_redirect(pars->token))
	{
		if (!(pars->next->token == ARG && pars->next->next->token == CMD))
			return (0);
		pars = pars->next;
		while (!is_redirect(pars->token))
			pars = pars->next;
		if (!is_arg(pars))
			return (0);
	}
	pars = tmp;
	return (1);
}
