/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:10 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/08 15:45:16 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_envp(char **new_env, int i)
{
    while (i >= 0)
    {
        free(new_env[i]);
        i--;
    }
    free(new_env);
}

//faire fonction qui cherche si la varaible existe deja, de plus, la variable ne peut etre utiliser que si caractere alphanum ou underscore

size_t      var_lenght(char *str)
{
    size_t  len;
    
    len = 0;
    while (str[len] != '=')
        len++;
    return (len);
}
int     new_or_replace(t_args *data, char *str)
{
    int     i;
    int     k;
    size_t  var_len;
    
    i = 0;
    var_len = var_lenght(str);
    while (data->envp[i])
    {
        k = 0;
        while (data->envp[i][k] && data->envp[i][k])
        {
            
        }
    }
}

void	ft_export(t_args *data, char *str)
{
    int     i;
    char    **new_env;
    
    i = 0;
    while (data->envp[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return ;
    i = 0;
    while (data->envp[i])
    {
        new_env[i] = ft_strdup(data->envp[i]);
        if (!new_env[i])
            free_envp(new_env, i);
        i++;
    }
    new_env[i] = ft_strdup(str);
    i++;
    new_env[i] = 0;
    i = 0;
    while (new_env[i] != 0)
    {
        printf("%s\n", new_env[i]);
        i++;
    }
    return ;
}

void	*ft_realloc(void **old, size_t old_c, size_t new_c)
{
	void **new;
	size_t i;

	i = 0;
	new = ft_calloc(sizeof(void *), new_c);
	if (!new)
		return (NULL);
	while (i < old_c)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return (new);
}