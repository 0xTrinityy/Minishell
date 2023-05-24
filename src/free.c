/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:30:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 18:37:24 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	malloc_sec(t_pars *pars, t_pars *new)
{
	ft_free(&pars);
	ft_free(&new);
	return (0);
}

int	malloc_sec2(t_pars *pars, char *tmp)
{
	ft_free(&pars);
	free(tmp);
	return (0);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	malloc_sec3(t_pars *pars, char *str, char **env)
{
	free(str);
	ft_free(&pars);
	ft_free_tab(env);
	exit(0);
}
