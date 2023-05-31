/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:40:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 12:05:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
	{
		printf("export: %s : not a valid identifier\n", str);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("export: %s : not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	changing_arg(t_data *data, char **new, char *str, size_t var_len)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], str, var_len) != NULL
			&& (data->env[i][var_len] == '='))
		{
			free(data->env[i]);
			i++;
		}
		else
		{
			new[k] = (data->env[i]);
			k++;
			i++;
		}
	}
	new[k] = 0;
	free(data->env);
}

static void	ft_unset_arg(t_data *data, char *str)
{
	int		i;
	int		flag;
	char	**new;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(str);
	flag = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], str, var_len) != NULL
			&& (data->env[i][var_len] == '='))
			flag = 1;
		i++;
	}
	if (flag != 1)
		return ;
	new = malloc(sizeof(char *) * (i));
	if (!new)
		return ;
	changing_arg(data, new, str, var_len);
	data->env = new;
}

void	ft_unset(t_pars **pars, t_data *data)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT
			&& (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		ft_unset_arg(data, (*pars)->str);
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
}
