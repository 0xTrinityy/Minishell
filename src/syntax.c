/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:40:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/31 16:51:11 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

static int	cmd_first(t_pars *pars, char **env)
{
	pars = pars->next;
	while (pars->token == ARG)
		pars = pars->next;
	if (!is_redirect(pars->token))
		return (0);
	pars = pars->next;
	if (pars == NULL || pars->token != ARG)
		return (0);
	pars = pars->next;
	if (pars != NULL && pars->token == PIPE)
		check_syntax(&pars->next, env);
	return (1);
}

int	check_syntax_redirect(t_pars *pars, char **env)
{
	t_pars	*tmp;

	tmp = pars;
	if (pars->token == CMD)
		return (cmd_first(pars, env));
	else if (is_redirect(pars->token))
	{
		if (!check_next(pars))
			return (0);
		pars = pars->next->next;
		if (pars != NULL && pars->token == CMD)
			pars = pars->next;
		while (pars != NULL && pars->token == ARG)
			pars = pars->next;
		if (!redirect_condition(pars, env))
			return (0);
		pars = tmp;
	}
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

static int	check_arg(t_pars **pars, char **env)
{
	t_pars	*tmp;

	tmp = *pars;
	if (check_redirect(*pars))
		return (check_syntax_redirect(*pars, env));
	if ((*pars)->token != CMD)
		return (0);
	*pars = (*pars)->next;
	while (*pars != NULL)
	{
		if ((*pars)->token == PIPE && (*pars)->next != NULL)
		{
			printf("%d\n", g_global);
			if (!check_syntax(&(*pars)->next, env))
				return (0);
			break ;
		}
		if ((*pars)->token != ARG)
			return (0);
		*pars = (*pars)->next;
	}
	*pars = tmp;
	return (1);
}

int	check_syntax(t_pars **pars, char **env)
{
	if (!check_arg(pars, env))
	{
		g_global = 2;
		return (0);
	}
	is_builtin(*pars);
	g_global = 0;
	check_error(*pars);
	return (1);
}
