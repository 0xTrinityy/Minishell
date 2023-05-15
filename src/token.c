/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:18:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/09 19:31:46 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static enum e_pars	check_pipe(enum e_pars token, char *str, enum e_token *ID)
{
	if (token == N_SORTED)
	{
		if (ft_strlen(str) != 1 || ID[0] != PIPE_C)
			return (token);
		token = PIPE;
	}
	return (token);
}

static enum e_pars	check_redirect(enum e_pars token, char *str)
{
	int	i;

	i = 0;
	if (token != N_SORTED)
		return (token);
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '>')
			token = R_OUTPUT;
		else if (str[0] == '<')
			token = R_INPUT;
		return (token);
	}
	while (str[i] == '>' && str[i])
	{
		i++;
		token = R_DOUTPUT;
	}
	while (str[i] == '<' && str[i])
	{
		i++;
		token = R_DINPUT;
	}
	return (token);
}

void	put_token(t_pars **pars, char **env)
{
	int		i;
	t_pars	*tmp;

	i = 0;
    (void) env;
	tmp = (*pars);
	while ((*pars) != NULL)
	{
		(*pars)->token = check_pipe((*pars)->token, (*pars)->str, (*pars)->ID);
		(*pars)->token = check_redirect((*pars)->token, (*pars)->str);
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
    give_cmd(*pars, 0);
    (*pars) = tmp;
}
