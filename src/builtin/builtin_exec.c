/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:48:27 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/21 14:34:54 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//mainn pour tester les built-in
int     main(int argc, char **argv, char **envp)
{
    t_args      data;
    
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    //ft_echo(&data);
    ft_pwd(envp);
    return (0);
}