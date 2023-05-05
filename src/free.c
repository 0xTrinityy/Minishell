/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:30:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/05 08:45:45 by luciefer         ###   ########.fr       */
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
