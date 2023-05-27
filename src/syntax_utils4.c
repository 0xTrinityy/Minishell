/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:43:13 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/27 11:30:59 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	check_error(t_pars *pars)
{
	if (pars->str[0] == '&' || pars->str[0] == ';' || pars->str[0] == '('
		|| pars->str[0] == ')' || pars->str[0] == '.')
		g_global = 2;
	else if (pars->str[0] == '/' || (pars->str[0] == '.' && pars->str[1] == '/')
		|| pars->str[0] == '~')
		g_global = 126;
	else if (!pars->str[0])
		g_global = 127;
}
