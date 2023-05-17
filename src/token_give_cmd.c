/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_give_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:49:44 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 15:49:46 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static enum e_pars	check_quoted(char *str, enum e_token *ID)
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

static enum e_pars	check_cmd(enum e_pars token, char *str, enum e_token *ID)
{
	if (token == N_SORTED)
	{
		token = check_quoted(str, ID);
		if (token == N_SORTED)
			token = TXT;
	}
	return (token);
}

void	give_cmd(t_pars *pars, int i)
{
	while (pars != NULL)
	{
		if (is_redirect(pars->token))
		{
			pars = pars->next;
			pars->token = check_cmd(pars->token, pars->str, pars->ID);
			if (pars->token == 0)
				pars->token = TXT;
		}
		if (pars->token == PIPE)
			give_cmd(pars->next, 0);
		if (i == 0 && pars->token == N_SORTED)
		{
			pars->token = CMD;
			i = 1;
		}
		else
			pars->token = check_cmd(pars->token, pars->str, pars->ID);
		if (pars->token == 0)
			pars->token = TXT;
		pars = pars->next;
	}
}
