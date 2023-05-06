/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:18:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/06 10:29:06 by luciefer         ###   ########.fr       */
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

static int    is_a_cmd(char *str, char **envp)
{
	char	**tab;
	char	*path;
	char	*cmd;

	tab = 0;
	path = 0;
	cmd = 0;
	path = find_path(envp);
	tab = ft_split(path, ':');
	cmd = get_cmd(tab, str);
	ft_free_tab(tab);
	printf("cmd = %s\n", cmd);
	if (cmd != NULL)
	{
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}

static enum e_pars	check_cmd(enum e_pars token, char *str, enum e_token *ID, char **env)
{
	if (token == N_SORTED)
	{
		if (is_a_cmd(str, env))
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

void	put_token(t_pars **pars, char **env)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = (*pars);
	while ((*pars) != NULL)
	{
		(*pars)->token = check_pipe((*pars)->token, (*pars)->str, (*pars)->ID);
		(*pars)->token = check_redirect((*pars)->token, (*pars)->str);
		(*pars)->token = check_cmd((*pars)->token, (*pars)->str, (*pars)->ID, env);
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
