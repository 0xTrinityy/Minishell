/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:39:43 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/31 16:52:40 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

int	check_next(t_pars *pars)
{
	if (pars->next != NULL)
	{
		if (pars->next->token == ARG)
		{
			if (pars->next->next != NULL && pars->next->next->token == CMD)
				return (1);
			return (1);
		}
	}
	return (0);
}

void	is_builtin(t_pars *pars)
{
	t_pars	*tmp;

	tmp = pars;
	while (pars != NULL)
	{
		if (pars->token == CMD)
		{
			if (strcmp(pars->str, "unset") == 0 || strcmp(pars->str,
					"pwd") == 0)
				pars->token = BUILTIN;
			else if (strcmp(pars->str, "cd") == 0)
				pars->token = BUILTIN;
			else if (strcmp(pars->str, "exit") == 0)
				pars->token = BUILTIN;
			else if (strcmp(pars->str, "export") == 0)
				pars->token = BUILTIN;
			else if (strcmp(pars->str, "echo") == 0)
				pars->token = BUILTIN;
			else if (strcmp(pars->str, "env") == 0)
				pars->token = BUILTIN;
		}
		pars = pars->next;
	}
	pars = tmp;
}

void	check_error(t_pars *pars)
{
	if (pars->str[0] == '&' || pars->str[0] == ';' || pars->str[0] == '('
		|| pars->str[0] == ')' || (pars->str[0] == '.' && !pars->str[1]))
	{
		print_error(&pars->str[0]);
		g_global = 2;
	}
	else if ((pars->str[0] == '/' && !pars->str[1]) || (pars->str[0] == '.'
			&& pars->str[1] == '/' && !pars->str[2]) || pars->str[0] == '~')
	{
		print_error(pars->str);
		g_global = 126;
	}
	else if (!pars->str[0])
		g_global = 127;
}

int	redirect_condition(t_pars *pars, char **env)
{
	if (pars != NULL && is_redirect(pars->token))
	{
		if (!check_syntax_redirect(pars, env))
			return (0);
	}
	if (pars != NULL && pars->token == PIPE)
	{
		if (!check_syntax(&pars->next, env))
			return (0);
	}
	return (1);
}
