/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:48:27 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/10 19:56:20 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//main pour tester les built-in
int     main(int argc, char **argv, char **envp)
{
    t_args      data;
    int     i;
    
    i = 0;
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    //ft_echo(&data);
    //ft_pwd(envp);
    data.envp = ft_export(&data, "Lucien=first-pick");
    data.envp = ft_export(&data, "ab=25");
    data.envp = ft_export(&data, "Lucien=second-pick");
    i = 0;
	while (data.envp[i] != 0)
    {
        printf("%s\n", data.envp[i]);
        i++;
    }

    return (0);
}

