/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:34:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 12:18:09 by tbelleng         ###   ########.fr       */
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

static void	exporting_arg(t_data *data, char *str, char **new_env)
{
	int	i;

	i = 0;
	while (data->env[i] != 0)
	{
		new_env[i] = (data->env[i]);
		if (!new_env[i])
		{
			free_envp(new_env, i);
			exit(1);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	i++;
	new_env[i] = 0;
}

static void	ft_export_arg(char *str, t_data *data)
{
	int		i;
	int		flag;
	char	**new_env;

	i = 0;
	flag = 0;
	if (new_or_replace(data, str) == 1)
	{
		flag = 1;
		new_value(data, str);
		return ;
	}
	while (data->env[i] != 0)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	exporting_arg(data, str, new_env);
	free(data->env);
	data->env = new_env;
}

void	*ft_realloc(void **old, size_t old_c, size_t new_c)
{
	void	**new;
	size_t	i;

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

void	ft_export(t_pars **pars, t_data *data)
{
	t_pars	*tmp;

	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	(*pars) = (*pars)->next;
	while ((*pars) != NULL && (is_redirect((*pars)->token) && (*pars)->token != PIPE))
	{
		if (valid_arg((*pars)->str))
			ft_export_arg((*pars)->str, data);
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
}
