/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:02:39 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/27 16:10:40 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

int	len_redirect(enum e_token *ID, char *str)
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

t_pars	*get_word(t_pars **pars, char *str, enum e_token *ID, t_pars *new)
{
	int	i;
	int	j;

	i = 0;
	j = ft_iter(str, ID) + 1;
	new = (t_pars *)ft_calloc(sizeof(t_pars), 1);
	if (!new)
		exit(malloc_sec(*pars, new));
	new->str = ft_calloc(sizeof(char), j + 1);
	if (!new->str)
		exit(malloc_sec(*pars, new));
	ft_strlcpy(new->str, str, j);
	new->id = (enum e_token *)ft_calloc(sizeof(enum e_token),
			ft_strlen(new->str) + 1);
	if (!new->id)
		exit(malloc_sec(*pars, new));
	put_id(new->str, new->id);
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

static int	simple_quote(char *str, t_pars **pars, char **env)
{
	if (str[0] == '"' || str[0] == '\'')
	{
		if (!str[1])
		{
			g_global = 2;
			(*pars) = (t_pars *)ft_calloc(sizeof(t_pars), 1);
			if (!(*pars))
				malloc_sec3(*pars, str, env);
			(*pars)->str = ft_calloc(sizeof(char), 2);
			if (!(*pars)->str)
				malloc_sec3(*pars, str, env);
			(*pars)->str[0] = str[0];
			(*pars)->str[1] = 0;
			(*pars)->id = (enum e_token *)ft_calloc(sizeof(enum e_token), 2);
			if (!(*pars)->id)
				malloc_sec3(*pars, str, env);
			(*pars)->id[0] = S_QUOTE;
			(*pars)->id[1] = FINISH;
			(*pars)->token = CMD;
			(*pars)->next = NULL;
			(*pars)->prev = NULL;
			return (0);
		}
	}
	return (1);
}

void	create_pars(t_pars **pars, char *str, enum e_token *ID, char **env)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	if (!simple_quote(str, pars, env))
	{
		return ;
	}
	while (str[i])
	{
		while (ID[i] == IFS && str[i])
			i++;
		if (ID[i] != FINISH)
		{
			tmp = get_word(pars, str + i, ID + i, tmp);
			if (pars)
				tmp->prev = *pars;
			_lstadd_back(tmp, pars);
		}
		i = i + ft_iter(str + i, ID + i);
	}
}
