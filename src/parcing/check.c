/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:18:10 by luciefer          #+#    #+#             */
/*   Updated: 2023/04/14 13:06:35 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_d_quote(t_list *new, char *str, enum e_token *ID)
{
	int	i;

	i = 1
	while (token[i] != D_QUOTE)
		i++;
	new->str = malloc(sizeof(char) * i + 1);
	if (!new->str)
		ft_free_all();
	i = 1;
	while (token[i] != D_QUOTE)
	{
		new->str[i] = str[i];
		i++;
	}
	new->e_parc = TXT_D;
}

void	ft_s_quote(t_list *new, char *str, enum e_token *ID)
{
	int	i;

	i = 1;
	while (ID[i] != S_QUOTE && ID[i] != FINISH)
		i++;
	new->str = malloc(sizeof(char) * i + 1);
	if (!new->str)
		ft_free_all();
	i = 1;
	while (ID[i] != S_QUOTE)
	{
		new->str[i] = str[i];
		i++;
	}
	new->e_parc = TXT_S;
}

void	ft_quoted(t_list *new, char *str, enum e_token *ID)
{
	if (ID[0] == D_QUOTE)
		ft_d_quote(new, str, ID);
	else
		ft_s_quote(new, str, ID);
}

void	ft_not_quoted(t_list *new, char *str, enum e_token *ID)
{
	if (is_cmd(new, str, ID))
		return ;
	is_expand(new, str, ID);
}

int	get_word(t_list *pars, char *str, enum e_token *ID)
{
	int	i;
	t_list	*new;

	i = 0;
	while (ID[i])
	{
		if (!*pars)
			new->prev = NULL;
		else
			new->prev = *pars;
		while (ID[i] == IFS)
			i++;
		if (ID[i] == D_QUOTE || ID[i] == S_QUOTE)
			ft_quoted(new, *str + i, *ID + i);
		else
			ft_not_quoted(new, *str + i, *ID + i);
		if (!*pars)
			*pars = new;
		else
			ft_last(*pars) = new;
		i++;
	}
}

