/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_replace_dollar2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:30:27 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 17:30:29 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_lst_add_between(t_pars *new, t_pars *pars)
{
	if (!pars)
		new->next = NULL;
	else
	{
		new->prev = pars;
		new->next = pars->next;
	}
	if (!pars)
		pars = new;
	else
		pars->next = new;
}

void	recreate_pars(t_pars *pars, char *str, enum e_token *ID)
{
	int		i;
	t_pars	*tmp;
	int		u;

	i = 0;
	u = 0;
	while (str[i])
	{
		while (ID[i] == IFS && str[i])
			i++;
		if (ID[i] != FINISH)
		{
			tmp = get_word(&pars, str + i, ID + i, tmp);
			_lst_add_between(tmp, pars);
			if (pars->next != NULL)
				pars = pars->next;
		}
		i = i + ft_iter(str + i, ID + i);
	}
	while (pars->prev != NULL)
	{
		pars = pars->prev;
	}
}

void	check_cmd_valid(t_pars *pars)
{
	int		i;
	char	**tab;

	i = 0;
	tab = 0;
	while (pars->str[i])
	{
		if (pars->ID[i] == IFS)
		{
			recreate_pars(pars, pars->str, pars->ID);
			pars = pars->next;
			pars->token = 1;
			i = 0;
		}
		i++;
	}
	return ;
}
