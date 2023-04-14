/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:34:05 by luciefer          #+#    #+#             */
/*   Updated: 2023/04/14 13:07:02 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	take_value(char *str, char *env)
{
	int	i;

	i = 1;
	while (env[i])
		i++;
	free(str);
	str = malloc(sizeof(char) * i + 1);
	i = 1;
	while (env[i])
	{
		str[i - 1] = env[i];
		i++;
	}
}

void	replace_expand(t_list *pars, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (pars->token != EXPAND || pars->next != NULL)
		pars = pars->next;
	if (pars->token == EXPAND)
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			if (ft_strncmp(pars->str, env[i], j) == 0)
				take_value(pars->str, env[i] + j);
			i++;
		}
	}
	pars = pars->prev;
}
