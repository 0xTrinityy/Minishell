/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:18:26 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 18:37:16 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

int	nb_fd(t_pars *pars)
{
	t_pars	*tmp;
	int		i;

	i = 0;
	tmp = pars;
	while (pars != NULL)
	{
		if (pars->token == PIPE)
			i += 2;
		if (is_redirect(pars->token))
			i++;
		pars = pars->next;
	}
	return (i);
}

void	ft_exit(t_pars *pars)
{
	int	i;

	i = 0;
	while (i < nb_fd(pars))
		close(i++);
	ft_free(&pars);
	g_global = 2;
	exit(0);
}
