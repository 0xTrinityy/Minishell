/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:47:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/05 10:46:21 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_global;

int	check_next(t_pars *pars)
{
	if (pars->next != NULL)
	{
		if (pars->next->token == ARG)
		{
			if (pars->next->next != NULL && pars->next->next->token == CMD)
				return (1);
			return (1);
		}
	}
	return (0);
}

int	check_binary(t_pars *pars)
{
	if (pars->str[0] == '.' && pars->str[1] == '/')
	{
		pars->token = CMD;
		return (1);
	}
    g_global = 127;
	return (0);
}
