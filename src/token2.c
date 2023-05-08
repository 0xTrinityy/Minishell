/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:56:39 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:10:23 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_pars	check_quoted(char *str, enum e_token *ID)
{
	int			i;
	enum e_pars	tmp;

	i = 0;
	tmp = 0;
	if (ID[i] == S_QUOTE)
	{
		while (ID[i] != S_QUOTE && str[i])
			i++;
		if (ID[i] == S_QUOTE)
			tmp = TXT_S;
	}
	else if (ID[i] == D_QUOTE)
	{
		while (ID[i] != D_QUOTE && str[i])
			i++;
		if (ID[i] == D_QUOTE)
			tmp = TXT_D;
	}
	return (tmp);
}
