/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:22:10 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/15 18:50:17 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void    builtin_exec(t_pars **pars, t_pipe *file, t_data *data)
{
	t_pars  *tmp;
	
    tmp = *pars;
    //printf("carre");
    //printf("%s\n", file->env[0]);
    while ((*pars) != NULL)
    {
        if ((*pars)->token == BUILTIN)
        {
            if (strcmp((*pars)->str, "unset") == 0)
                ft_unset(pars, data);
            else if (strcmp((*pars)->str, "pwd") == 0)
                ft_pwd(data);
            /*else if (strcmp((*pars)->str, "cd") == 0)
                ft_cd(pars, file);*/
            /*else if (strcmp((*pars)->str, "exit") == 0)
                ft_exit(pars, file);*/
            else if (strcmp((*pars)->str, "export") == 0)
                ft_export(pars, data);
            else if (strcmp((*pars)->str, "echo") == 0)
                ft_echo(pars, file);
            else if (strcmp((*pars)->str, "env") == 0)
                ft_env(data);
            break;
        }
    }
    *pars = tmp;
    return ;
}

void    builtin_exe_mult(t_pars **pars, t_pipe *file, t_data *data)
{
	t_pars  *tmp;
	int     count;
	
    tmp = *pars;
    count = 0;
    while (count != file->pidx)
    {
        if ((*pars)->token == PIPE)
            count++;
        (*pars) = (*pars)->next;
    }
    while ((*pars) != NULL && (*pars)->token != PIPE)
    {
        if ((*pars)->token == BUILTIN)
        {
            if (strcmp((*pars)->str, "unset") == 0)
                ft_unset(pars, data);
            else if (strcmp((*pars)->str, "pwd") == 0)
                ft_pwd(data);
            /*else if (strcmp((*pars)->str, "cd") == 0)
                ft_cd(pars, file);*/
            /*else if (strcmp((*pars)->str, "exit") == 0)
                ft_exit(pars, file);*/
            else if (strcmp((*pars)->str, "export") == 0)
                ft_export(pars, data);
            else if (strcmp((*pars)->str, "echo") == 0)
                ft_echo(pars, file);
            else if (strcmp((*pars)->str, "env") == 0)
                ft_env(data);
            break;
        }
    }
    *pars = tmp;
    return ;
}