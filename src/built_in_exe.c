/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:22:10 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 09:42:32 by tbelleng         ###   ########.fr       */
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
            /*if (strcmp((*pars)->str, "unset") == 0)
                ft_unset(pars, file);*/
            if (strcmp((*pars)->str, "pwd") == 0)
                ft_pwd(file);
            /*else if (strcmp((*pars)->str, "cd") == 0)
                ft_cd(pars, file);*/
            /*else if (strcmp((*pars)->str, "exit") == 0)
                ft_exit(pars, file);*/
            else if (strcmp((*pars)->str, "export") == 0)
                ft_export(pars, file);
            else if (strcmp((*pars)->str, "echo") == 0)
                ft_echo(pars, file);
            else if (strcmp((*pars)->str, "env") == 0)
                ft_env(file);
            break;
        }
    }
    return ;
}