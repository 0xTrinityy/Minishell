/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:48:27 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/09 16:28:31 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//main pour tester les built-in
/*int     main(int argc, char **argv, char **envp)
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
}*/

void	select_cmd(char **cmd)
{
//	char	str[6];

	/*while (cmd[i] || cmd[i] != ' ')
	{
		str[i] = cmd[i];
		i++;
	}*/
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		ft_echo(cmd);
}

void	exec_cmd(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	select_cmd(cmd);
}
