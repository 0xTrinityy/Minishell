/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:22:10 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 07:28:42 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void    builtin_exec(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	
    tmp = *pars;
    while ((*pars) != NULL)
    {
        if ((*pars)->token == BUILTIN)
        {
            if (strcmp((*pars)->str, "unset") == 0 || strcmp((*pars)->str, "pwd") == 0)
                (*pars)->token = BUILTIN;
            else if (strcmp((*pars)->str, "cd") == 0)
                (*pars)->token = BUILTIN;
            else if (strcmp((*pars)->str, "exit") == 0)
                (*pars)->token = BUILTIN;
            else if (strcmp((*pars)->str, "export") == 0)
                (*pars)->token = BUILTIN;
            else if (strcmp((*pars)->str, "echo") == 0)
                (*pars)->token = BUILTIN;
            else if (strcmp((*pars)->str, "env") == 0)
                (*pars)->token = BUILTIN;
        }
        (*pars) = (*pars)->next;
    }
}