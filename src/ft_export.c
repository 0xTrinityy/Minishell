/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:34:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/22 12:04:52 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


static void	free_envp(char **new_env, int i)
{
	while (i >= 0)
	{
		free(new_env[i]);
		i--;
	}
	free(new_env);
}

char	*var_trimmed(char *str)
{
	int	len;
	int		i;
	char	*tab;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tab = malloc(sizeof(char) * (len + 1));
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

int	new_or_replace(t_data *data, char *str)
{
	int		i;
	char	*var;
	size_t	var_len;

	i = 0;
	var_len = to_equal(str);
	var = var_trimmed(str);
	printf("ici la var vaut = %s\n", var);
	while (data->env[i] != 0)
	{
		if (ft_strnstr(data->env[i], var, var_len) != NULL)
		{
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
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
    str[i] = 0;
    free(old);
    return (new);
}


void new_value(t_data *data, char *str)
{
    int     i;
    int     j;
    char    *var;
    size_t  var_len;
    
    i = 0;
    j = 0;
    var_len = to_equal(str);
	var = var_trimmed(str);
	while (data->env[i])
	{
	    if (ft_strnstr(data->env[i], var, var_len) != NULL)
	    {
	        free(data->env[i]);
	        data->env[i] = ft_strdup(str);
	        free (var);
	        break ;
		}
	    i++;
	}
}

static void	ft_export_arg(char *str, t_data *data)
{
	int		i;
	int     flag;
	char	**new_env;
	//char    **tmp;
	
	i = 0;
	flag = 0;
	if (new_or_replace(data, str) == 1)
	{
		flag = 1;
		printf("ici on replace la value");
		new_value(data, str);
		return ;
	}
    while (data->env[i] != 0)
    {
        i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (data->env[i] != 0)
	{
		new_env[i] = (data->env[i]);
		if (!new_env[i])
		{
			free_envp(new_env, i);
			exit (1);
		}
		i++;
	}
	printf("ICI, AVANT AJOUT, ENVP VAUT %d\n", i);
	new_env[i] = ft_strdup(str);
	i++;
	new_env[i] = 0;
	i = -1;
	/*while (data->env[++i])
		free(data->env[i]);
	free(data->env);*/
	data->env = new_env;
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

void    ft_export(t_pars **pars, t_data *data)
{
	t_pars  *tmp;
	
	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		ft_export_arg((*pars)->str, data);
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
}
