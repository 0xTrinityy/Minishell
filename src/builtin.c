/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:44:17 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/15 18:10:36 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//****************************** ECHO CMD ********************************
void    echo(int argc, char **argv)
{
    int     i;
    int     flag;

    i = 1;
    flag = 0;
    if (!ft_strncmp(argv[1], "-n", 2))
    {
        flag = 1;
        i++;
    }
    while (i < argc)
    {
        printf("%s", argv[i]);
        i++;
    }
    if (flag == 1)
        printf("%%");
    printf("\n");
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

//****************************** CD CMD ********************************





//****************************** MAIN ********************************
int     main(int argc, char **argv, char **envp)
{
    echo(argc, argv);
    //pwd(envp);
    return (0);
}