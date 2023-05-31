/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:39:15 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/31 16:39:40 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

static int	check_token(t_pars *pars)
{
	t_pars	*tmp;

	tmp = pars;
	while (pars != NULL)
	{
		if (is_redirect(pars->token))
		{
			if (ft_strlen(pars->str) > 2)
			{
				g_global = 2;
				pars->str[2] = 0;
				print_error(pars->str);
				return (0);
			}
		}
		pars = pars->next;
	}
	pars = tmp;
	return (1);
}

static int	check_ifs(char *str, enum e_token *ID)
{
	int	i;

	i = 0;
	while ((ID[i] == IFS_TMP && str[i]) || str[i] == '!' || str[i] == ':')
		i++;
	if (ID[i] != FINISH)
		return (0);
	return (1);
}

int	ft_free_start(t_start *start)
{
	free(start->str);
	free(start->id);
	return (2);
}

int	ft_parsing(t_pars **pars, char **str, char **env)
{
	t_start	start;
	int		i;

	i = 0;
	start.id = 0;
	start.env = env;
	start.str = ft_strdup(*str);
	free(*str);
	start.id = put_id(start.str);
	if (!ft_expand(&start))
		return (ft_free_start(&start));
	put_token(pars);
	if (check_ifs(start.str, start.id))
		return (ft_free_start(&start));
	create_pars(&start, pars);
	put_token(pars);
	if (!check_token(*pars))
		return (ft_free_start(&start));
	if (!check_syntax(pars, start.env))
	{
		print_error((*pars)->str);
	}
	ft_free_start(&start);
	return (0);
}
