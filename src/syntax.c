/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:58:14 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 15:33:33 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

static int	replace_expand(t_pars *pars, char **env)
{
	t_pars	*tmp;
	char	*str;

	(void)env;
	str = 0;
	tmp = pars;
	while (pars != NULL)
	{
		if (pars->token == TXT_S)
			del_quote(pars);
		else if (pars->token == EXPAND || pars->token == TXT
			|| pars->token == TXT_D || pars->token == CMD)
			replace_dollar(pars, env, str);
		pars = pars->next;
	}
	pars = tmp;
	return (1);
}

static int	check_redirect(t_pars *pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = pars;
	while (pars != 0 && pars->token != PIPE)
	{
		if (is_redirect(pars->token))
		{
			pars = tmp;
			return (1);
		}
		else
			pars = pars->next;
	}
	pars = tmp;
	return (0);
}

static int	check_arg(t_pars *pars, char **env)
{
	t_pars	*tmp;

	tmp = pars;
	if (check_redirect(pars))
		return (check_syntax_redirect(pars, env));
	if (pars->token != CMD)
		return (0);
	pars = pars->next;
	while (pars != NULL)
	{
		if (pars->token == PIPE && pars->next != NULL)
		{
			check_syntax(pars->next, env);
			break ;
		}
		if (pars->token != ARG)
		{
			pars = tmp;
			return (0);
		}
		pars = pars->next;
	}
	pars = tmp;
	return (1);
}

static void	replace_arg(t_pars *pars)
{
	t_pars	*tmp;

	tmp = pars;
    while (pars->token != CMD)
        pars = pars->next;
    if (pars != NULL)
	    pars = pars->next;
	while (pars != NULL && (pars->token == ARG || pars->token == CMD))
	{
		pars->token = ARG;
		pars = pars->next;
	}
	pars = tmp;
	return ;
}

t_pars	*check_syntax(t_pars *pars, char **env)
{
	(void)env;
	replace_arg(pars);
	replace_expand(pars, env);
	if (pars->token == CMD)
	{
		if (pars->next != NULL && pars->next->token == CMD)
		{
			pars = pars->next;
			give_cmd(pars, 1);
			check_syntax(pars, env);
		}
	}
	if (!check_arg(pars, env))
	{
		g_global = 127;
		return (pars);
	}
	is_builtin(pars);
	return (pars);
}

// tmp2 = pars;
// printf("str:");
// while(pars != NULL)
// {
//     printf(" %s", pars->str);
//     printf(" (%u)", pars->token);
//     pars = pars->next;
// }
// pars = tmp2;
// printf("\n");
// exit (0);
