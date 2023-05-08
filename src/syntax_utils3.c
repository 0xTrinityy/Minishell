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

void    is_builtin(t_pars *pars)
{
    t_pars  *tmp;

    tmp = pars;
    while (pars != NULL)
    {
        if (pars->token == CMD)
        {
            if (strcmp(pars->str, "unset") == 0 || strcmp(pars->str, "pwd") == 0)
                pars->token = BUILTIN;
            else if (strcmp(pars->str, "cd") == 0)
                pars->token = BUILTIN;
            else if (strcmp(pars->str, "exit") == 0)
                pars->token = BUILTIN;
            else if (strcmp(pars->str, "export") == 0)
                pars->token = BUILTIN;
            else if (strcmp(pars->str, "echo") == 0)
                pars->token = BUILTIN;
            else if (strcmp(pars->str, "env") == 0)
                pars->token = BUILTIN;
        }
        pars = pars->next;
    }
    pars = tmp;
}
