/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/12 15:40:12 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//TO DO 
	//il faut refresh le OLD PWD et le PWD.


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
    if (chdir(str) != 0) 
    {
        perror("Minishell: cd :");
        return 1;
    }
    printf("Current working directory: %s\n", getcwd(NULL, 0));
    new_pwd(data);
    return 0;
}
