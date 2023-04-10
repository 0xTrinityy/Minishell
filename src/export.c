/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:10 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/10 20:20:23 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp(char **new_env, int i)
{
	while (i >= 0)
	{
		free(new_env[i]);
		i--;
	}
	free(new_env);
}

//faire fonction qui cherche si la varaible existe deja, de plus,
	//la variable ne peut etre utiliser que si caractere alphanum ou underscore

char	*var_trimmed(char *str)
{
	size_t	len;
	int		i;
	char	*tab;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tab = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

size_t	to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (i);
}

int	new_or_replace(t_args *data, char *str)
{
	int		i;
	char	*var;
	size_t	var_len;

	i = 0;
	var_len = to_equal(str);
	var = var_trimmed(str);
	while (data->envp[i])
	{
		if (ft_strnstr(data->envp[i], var, var_len) != NULL)
			return (1);
		i++;
	}
	return (0);
}

char    *realloc_value(char *old, char *str, int size)
{
    int     i;
    char    *new;
    
    i = 0;
    new = malloc(sizeof(char) * (size + 1));
    if (!new)
        return (NULL);
    while (str[i] != '\0')
    {
        new[i] = str[i];
        i++;
    }
    free(old);
    return (new);
}


void new_value(t_args *data, char *str)
{
    int     i;
    int     j;
    char    *var;
    size_t  var_len;
    
    i = 0;
    j = 0;
    var_len = to_equal(str);
	var = var_trimmed(str);
	while (data->envp[i])
	{
	    if (ft_strnstr(data->envp[i], var, var_len) != NULL)
	    {
	        j = ft_strlen(str);
	        data->envp[i] = realloc_value(data->envp[i], str, j);
	        /*while (data->envp[i] != 0)
	            i++;
	        j = ft_strlen(str);
	        data->envp[i] = malloc(sizeof(char) * (j + 1));
	        j = 0;
	        while (str[j] != '\0')
	        {
	            data->envp[i][j] = str[j];
	            j++;
	        }*/
        }
	    i++;
	}
}

char	**ft_export(t_args *data, char *str)
{
	int		i;
	char	**new_env;
	
	i = 0;
	if (new_or_replace(data, str) == 1)
	{
	    printf("DEBUG\n");
		new_value(data, str);
    }
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
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
	return (new_env);
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