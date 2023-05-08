/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:30:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/06 10:30:21 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	malloc_sec(t_pars *pars, t_pars *new)
{
	ft_free(pars);
	ft_free(new);
	return (0);
}

int	malloc_sec2(t_pars *pars, char *tmp)
{
	ft_free(pars);
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
