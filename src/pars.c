/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:02:39 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 14:06:36 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_redirect(enum e_token *ID)
{
	int	i;

	i = 0;
	if (ID[i] == PIPE_C)
		return (1);
	while (ID[i] == REDIRECT)
		i++;
	return (i);
}

static int	ft_iter(char *str, enum e_token *ID)
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
		i = len_redirect(ID);
	else
	{
		while (ID[i] != IFS && str[i] && ID[i] != REDIRECT && ID[i] != PIPE_C)
			i++;
	}
	return (i);
}

static t_pars	*get_word(t_pars **pars, char *str, enum e_token *ID)
{
	int		i;
	int		j;
	t_pars	*new;

	i = 0;
	j = ft_iter(str, ID);
	new = (t_pars *)malloc(sizeof(t_pars));
	new->str = malloc(sizeof(char) * j + 1);
	if (!new->str)
		ft_free_all();
	while (i < j)
	{
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = 0;
	new->ID = (enum e_token *) malloc(sizeof(enum e_token)
			* (ft_strlen(new->str) + 1));
	if (!new->ID)
	{
		free(new->ID);
		ft_free_all();
	}
	put_id(new->str, new->ID);
	new->token = N_SORTED;
	new->next = NULL;
	if (!*pars)
		new->prev = NULL;
	else
		new->prev = *pars;
	return (new);
}

static void	_lstadd_back(t_pars *tmp, t_pars **pars)
{
	if (!*pars)
		*pars = tmp;
	else
		ft_lstlast_(*pars)->next = tmp;
}

int	create_pars(t_pars **pars, char *str, enum e_token *ID)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	while (str[i])
	{
		while (ID[i] == IFS && str[i])
			i++;
		if (!str[i])
			return (1);
		if (ID[i] != FINISH)
		{
			tmp = get_word(pars, str + i, ID + i);
			if (pars)
				tmp->prev = *pars;
			_lstadd_back(tmp, pars);
		}
		i = i + ft_iter(str + i, ID + i);
	}
	return (1);
}
