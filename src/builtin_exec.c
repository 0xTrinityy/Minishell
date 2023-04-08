/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:48:27 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/08 16:40:38 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//main pour tester les built-in
int     main(int argc, char **argv, char **envp)
{
    t_args      data;
    
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    //ft_echo(&data);
    //ft_pwd(envp);
    ft_export(&data, "new1=10");
    ft_export(&data, "new2=20");
    ft_export(&data, "new1=30");
    return (0);
}