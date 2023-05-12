/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:57:38 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/06 16:38:24 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int  g_global;

void	ft_free_all(void)
{
	exit (0);
}

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
				return (0);
            }
		}
		pars = pars->next;
	}
	pars = tmp;
	return (1);
}

static int  check_ifs(char *str, enum e_token *ID) 
{
    int i;

    i = 0;
    while (ID[i] == IFS && str[i])
        i++;
    if (ID[i] != FINISH)
        return (0);
    return (1);
}

int	ft_parsing(t_pars **pars, char *str, char **env)
{
	enum e_token	*id;

	(void) env;
	*pars = 0;
	id = (enum e_token *) malloc(sizeof(enum e_token) * (ft_strlen(str) + 1));
	if (!id)
	{
		free(id);
		ft_free_all();
	}
	if (!str)
		return (0);
	put_id(str, id);
    if (check_ifs(str, id))
        return (2);
    create_pars(pars, str, id);
	free(id);
	put_token(pars, env);
	if (!check_token(*pars))
		return (0);
	return (check_syntax(*pars, env));
}
