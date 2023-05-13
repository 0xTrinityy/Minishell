/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:34:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 09:44:23 by tbelleng         ###   ########.fr       */
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

int	new_or_replace(t_pipe *file, char *str)
{
	int		i;
	char	*var;
	size_t	var_len;

	i = 0;
	var_len = to_equal(str);
	var = var_trimmed(str);
	while (file->env[i])
	{
		if (ft_strnstr(file->env[i], var, var_len) != NULL)
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


void new_value(t_pipe *file, char *str)
{
    int     i;
    int     j;
    char    *var;
    size_t  var_len;
    
    i = 0;
    j = 0;
    var_len = to_equal(str);
	var = var_trimmed(str);
	while (file->env[i])
	{
	    if (ft_strnstr(file->env[i], var, var_len) != NULL)
	    {
	        j = ft_strlen(str);
	        file->env[i] = realloc_value(file->env[i], str, j);
	        break ;
		}
	    i++;
	}
}

/*void	msg_error(char *err, char *str)
{
	perror(err);
	printf("bash: export: %s : ", str);
	exit(1);
}*/

/*int     valid_variable(char *str)
{
	int     i;
	
	i = 0;
	while(str[i] != '=' && str[0] != '=')
	{
		if (str[i] == '_')
			i++;
		else if (ft_isalnum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}*/

static void	ft_export_arg(char *str, t_pipe *file)
{
	int		i;
	int     flag;
	char	**new_env;
	char    **tmp;
	
	i = 0;
	flag = 0;
	/*if (!valid_variable(str))
	{	
		printf("bash: export: %s : not a valid identifier", str);
		exit(1);
		//msg_error(INVALID_ID, str);
	}*/
	if (new_or_replace(file, str) == 1)
	{
		flag = 1;
		new_value(file, str);
	}
    while (file->env[i])
    {
        i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (file->env[i])
	{
		new_env[i] = ft_strdup(file->env[i]);
		if (!new_env[i])
		{
			free_envp(new_env, i);
			exit (1); //A CHANGER AVEC LE VRAI EXIT
		}
		i++;
	}
	if (flag == 1)
	{
		tmp = file->env;
		free(tmp);
		file->env = new_env;
		return ;
	}
	new_env[i] = ft_strdup(str);
	i++;
	new_env[i] = 0;
	tmp = file->env;
	free(tmp);
	file->env = new_env;
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

void    ft_export(t_pars **pars, t_pipe *file)
{
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		ft_export_arg((*pars)->str, file);
		(*pars) = (*pars)->next;
	}
	return ;
}
