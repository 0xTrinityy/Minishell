/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/13 14:33:35 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//TO DO 
	//il faut refresh le OLD PWD

char    *realloc_oldpwd(char *old, char *before, int oldsize)
{
    int     i;
    int     len;
    char    *oldpwd;
    char    *new;
    
    i = 0;
    len = 0;
    (void)old;
    oldpwd = "OLDPWD=";
    new = malloc(sizeof(char) * (oldsize + 8));
    if (!new)
        return (NULL);
    while (oldpwd[i] != '\0')
    {
        new[i] = oldpwd[i];
        i++;
    }
    printf("i equal %d\n", i);
    printf("%s\n\n\n\n", before);
    while (before[len] != '\0')
    {
        new[i] = before[len];
        i++;
        len++;
    }
    return (new);
}

void    new_old(t_args *data, char *before, int oldsize)
{
    
	int     i;
	
	i = 0;
	while (data->envp[i])
	{
		if(ft_strnstr(data->envp[i], "OLDPWD=", 7))
			data->envp[i] = realloc_oldpwd(data->envp[i], before, oldsize);
		i++;
	}
}

char    *realloc_pwd(char *old)
{
    int     i;
    int     len;
    char    *path;
    char    *new;
    
    i = 4;
    (void)old;
    path = getcwd(NULL, 0);
    len = ft_strlen(path);
    new = malloc(sizeof(char) * (len + 5));
    if (!new)
        return (NULL);
    new[0] = 'P';
    new[1] = 'W';
    new[2] = 'D';
    new[3] = '=';
    len = 0;
    while (path[len] != '\0')
    {
        new[i] = path[len];
        i++;
        len++;
    }
    new[i] = 0;
    free(path);
    return (new);
}

void    new_pwd(t_args *data)
{
	int     i;
	
	i = 0;
	while (data->envp[i])
	{
		if(ft_strnstr(data->envp[i], "PWD=", 4))
			data->envp[i] = realloc_pwd(data->envp[i]);
		i++;
	}
}

int    ft_cd(t_args *data, char *str)
{
    char    *old;
    int     oldsize;
    
    old = getcwd(NULL, 0);
    oldsize = ft_strlen(old);
    if (chdir(str) != 0) 
    {
        free(old);
        perror("Minishell: cd :");
        return 1;
    }
    printf("Current working directory: %s\n", getcwd(NULL, 0));
    new_pwd(data);
    new_old(data, old, oldsize);
    free(old);
    return 0;
}
