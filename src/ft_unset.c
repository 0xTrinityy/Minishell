/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:40:53 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/23 21:43:02 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void    ft_unset_arg(t_data *data, char *str)
{
	int     i;
	int     k;
	int     flag;
	char    **new;
	size_t  var_len;
	
	i = 0;
	k = 0;
	var_len = ft_strlen(str);
	flag = 0;
	while(data->env[i])
	{
		if (ft_strnstr(data->env[i], str, var_len) != NULL && (data->env[i][var_len] == '='))
			flag = 1;
		i++;
	}
	if (flag != 1)
		return ;
	new = malloc(sizeof(char *) * (i));
	if (!new)
		return ;
	i = 0;
	while(data->env[i])
	{
		if (ft_strnstr(data->env[i], str, var_len) != NULL && (data->env[i][var_len] == '='))
		{
			printf("VALUE FOUND!\n");
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
	data->env = new;
}

void    ft_unset(t_pars **pars, t_data *data)
{
	int i;
	t_pars  *tmp;
	
	i = 0;
	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	(*pars) = (*pars)->next;
	while ((*pars) != NULL && ((*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT && (*pars)->token != PIPE))
	{
		ft_unset_arg(data, (*pars)->str);
		(*pars) = (*pars)->next;
	}
	*pars = tmp;
}