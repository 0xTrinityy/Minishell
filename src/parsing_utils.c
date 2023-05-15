/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:34:13 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:14:08 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect(enum e_pars token)
{
	if (token == R_INPUT)
		return (1);
	else if (token == R_OUTPUT)
		return (1);
	else if (token == R_DINPUT)
		return (1);
	else if (token == R_DOUTPUT)
		return (1);
	else
		return (0);
}

t_pars	*ft_lstlast_(t_pars *lst)
{
	while (lst->next != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
