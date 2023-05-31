/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:41:09 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/30 16:43:02 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

static int	ft_quote(t_start *start, int pos, enum e_token quote)
{
	int				i;
	char			*tmp;
	enum e_token	*id_tmp;

	i = 1;
	id_tmp = start->id + pos;
	tmp = start->str + pos;
	while (tmp[i] && id_tmp[i] != quote)
		i++;
	if (id_tmp[i] == FINISH)
	{
		g_global = 1;
		ft_putstr_fd("minishell: Quote does not closed\n", 1);
		return (-1000000);
	}
	start->str = del_quote(start, quote);
	check_id(start);
	return (pos + i - 2);
}

static int	leave_quote(t_start *start)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(start->str))
	{
		if (start->id[i] == D_QUOTE)
			i = ft_quote(start, i, D_QUOTE);
		else if (start->id[i] == S_QUOTE)
			i = ft_quote(start, i, S_QUOTE);
		if (i < 0)
			return (0);
		i++;
	}
	return (1);
}

static int	find_dollar(t_start *start, char *str, int pos)
{
	start->str = get_value(start, str, pos);
	free(start->id);
	start->id = put_id(start->str);
	return (pos);
}

int	ft_expand(t_start *start)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(start->str))
	{
		if (start->id[i] == S_QUOTE)
		{
			while (start->str[++i] && start->id[i] != S_QUOTE)
				;
		}
		else if (start->id[i] == D_QUOTE)
		{
			while (start->str[++i] && start->id[i] != D_QUOTE)
			{
				if (start->id[i] == DOLLAR)
					find_dollar(start, start->str + i, i);
			}
		}
		if (start->id[i] == DOLLAR)
			i = find_dollar(start, start->str + i, i);
		i++;
	}
	return (leave_quote(start));
}
