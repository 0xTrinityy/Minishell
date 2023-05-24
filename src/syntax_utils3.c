/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:47:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 15:51:33 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	del_quote(t_pars *pars)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = malloc(sizeof(char) * ft_strlen(pars->str));
	while (i < ((int)ft_strlen(pars->str) - 1))
	{
		tmp[i - 1] = pars->str[i];
		i++;
	}
	tmp[i - 1] = 0;
    free(pars->ID);
	pars->ID = (enum e_token *)malloc(sizeof(enum e_token) * (ft_strlen(tmp)
				+ 1));
	if (!pars->ID)
	{
		free(pars->ID);
		exit (0);
	}
	put_id(tmp, pars->ID);
    free(pars->str);
	pars->str = tmp;
	pars->token = ARG;
	return ;
}

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

int	check_binary(t_pars *pars)
{
	if (pars->str[0] == '.' && pars->str[1] == '/')
	{
		pars->token = CMD;
		return (1);
	}
	g_global = 127;
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
