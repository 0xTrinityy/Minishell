/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:44:17 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/14 10:27:00 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//****************************** ECHO CMD ********************************
void    echo(int argc, char **argv)
{
    int     i;

    i = 0;
    while (i < argc)
    {
        printf("%s", argv[i]);
        i++;
    }
    write(1, "/n", 1);
}

//****************************** PWD CMD ********************************
char	*find_path(char **envp)
{
	while (ft_strncmp("OLDPWD", *envp, 6))
		envp++;
	return (*envp + 7);
}

void    pwd(char **envp)
{
    char    *path;

    path = find_path(envp);
    printf("%s\n", path);
}

//****************************** MAIN ********************************
int     main(int argc, char **argv, char **envp)
{
    //echo(argc, argv);
    pwd(envp);
    return (0);
}