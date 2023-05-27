/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:34:13 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/27 11:33:47 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

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

void	check_pipe(t_pars *pars)
{
	t_pars	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = pars;
	while (pars != NULL)
	{
		if (pars->token == CMD || pars->token == BUILTIN)
			i++;
		else if (pars->token == PIPE)
			j++;
		pars = pars->next;
	}
	pars = tmp;
	if (i != j + 1)
		g_global = 2;
	return ;
}

int	ft_iter(char *str, enum e_token *ID)
{
	int				i;
	enum e_token	j;

	i = 0;
	if (ID[i] == D_QUOTE || ID[i] == S_QUOTE)
	{
		j = ID[i];
		i++;
		while ((ID[i] != j && ID[i] != j) && str[i])
			i++;
		if (!str[i])
			return (0);
		else
			i++;
	}
	else if (ID[i] == REDIRECT || ID[i] == PIPE_C)
		i = len_redirect(ID, str);
	else
	{
		while (ID[i] != IFS && str[i] && ID[i] != REDIRECT && ID[i] != PIPE_C
			&& ID[i] != D_QUOTE && ID[i] != S_QUOTE)
			i++;
	}
	return (i);
}
