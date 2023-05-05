/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:18:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/05 11:39:38 by luciefer         ###   ########.fr       */
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

int	cmd_comp(char *cmd)
{
	if (strcmp(cmd, "unset") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (2);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else
		return (0);
}

static enum e_pars	check_cmd(enum e_pars token, char *str, enum e_token *ID)
{
	if (token == N_SORTED)
	{
		if (cmd_comp(str))
			token = CMD;
		else
		{
			token = check_quoted(str, ID);
			if (token == N_SORTED)
				token = TXT;
		}
	}
	return (token);
}

void	put_token(t_pars **pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = (*pars);
	while ((*pars) != NULL)
	{
		(*pars)->token = check_pipe((*pars)->token, (*pars)->str, (*pars)->ID);
		(*pars)->token = check_redirect((*pars)->token, (*pars)->str);
		(*pars)->token = check_cmd((*pars)->token, (*pars)->str, (*pars)->ID);
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	while ((*pars) != NULL)
	{
		if ((*pars)->next != 0 && is_redirect((*pars)->token)
			&& (*pars)->next->token == CMD)
			(*pars)->next->token = ARG;
		*pars = (*pars)->next;
	}
	(*pars) = tmp;
}