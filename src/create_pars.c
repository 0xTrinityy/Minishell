/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:37:27 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/30 16:37:28 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_redirect(enum e_token *ID, char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	if (ID[i] == PIPE_C)
		return (1);
	while (ID[i] == REDIRECT && str[i] == c)
		i++;
	return (i);
}

static int	ft_iter(char *str, enum e_token *ID)
{
	int	i;

	i = 0;
	if (ID[i] == REDIRECT || ID[i] == PIPE_C)
		i = len_redirect(ID, str);
	else
	{
		while (ID[i] != IFS_TMP && str[i] && ID[i] != REDIRECT
			&& ID[i] != PIPE_C)
			i++;
	}
	return (i);
}

static t_pars	*get_word(t_pars **pars, t_start *start, int pos, t_pars *new)
{
	int	i;
	int	j;

	i = 0;
	j = ft_iter(start->str + pos, start->id + pos) + 1;
	new = (t_pars *)ft_calloc(sizeof(t_pars), 1);
	if (!new)
		exit(ft_free_3(*pars, new, start));
	new->str = ft_calloc(sizeof(char), j + 1);
	if (!new->str)
		exit(ft_free_3(*pars, new, start));
	ft_strlcpy(new->str, start->str + pos, j);
	new->id = put_id(new->str);
	new->token = N_SORTED;
	new->next = NULL;
	new->prev = *pars;
	return (new);
}

static void	_lstadd_back(t_pars *tmp, t_pars **pars)
{
	t_pars	*last;

	if (*pars == NULL)
	{
		tmp->prev = NULL;
		*pars = tmp;
	}
	else
	{
		last = ft_lstlast_(*pars);
		tmp->prev = last;
		last->next = tmp;
	}
}

void	create_pars(t_start *start, t_pars **pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	while (start->str[i])
	{
		while (start->id[i] == IFS_TMP)
			i++;
		if (start->id[i] != FINISH)
		{
			tmp = get_word(pars, start, i, tmp);
			if (pars)
				tmp->prev = *pars;
			_lstadd_back(tmp, pars);
		}
		i = i + ft_iter(start->str + i, start->id + i);
	}
}
