/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:34:13 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:14:08 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_global;

int	is_redirect(enum e_pars token)
{
	if (token == R_INPUT)
		return (1);
	else if (token == R_OUTPUT)
		return (1);
	else if (token == R_DINPUT)
		return (1);
	else if (token == R_DOUTPUT)
		return (1);
	else
		return (0);
}

t_pars	*ft_lstlast_(t_pars *lst)
{
	while (lst->next != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void    check_pipe(t_pars *pars)
{
    t_pars  *tmp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    tmp = pars;
    while(pars != NULL)
    {
        if (pars->token == CMD)
            i++;
        else if (pars->token == PIPE)
            j++;
        pars = pars->next;
    }
    pars = tmp;
    if (i != j + 1)
        g_global = 2;
    return ;
}
