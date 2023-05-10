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

// static int    is_a_cmd(char *str, char **envp)
// {
// 	char	**tab;
// 	char	*path;
// 	char	*cmd;
//
// 	tab = 0;
// 	path = 0;
// 	cmd = 0;
// 	path = find_path(envp);
// 	tab = ft_split(path, ':');
// 	cmd = get_cmd(tab, str);
// 	ft_free_tab(tab);
// 	if (cmd != NULL)
// 	{
// 		free(cmd);
// 		return (1);
// 	}
// 	free(cmd);
// 	return (0);
// }
//
// static int	is_a_builtin(char *cmd)
// {
// 	if (strcmp(cmd, "unset") == 0)
// 		return (1);
// 	else if (strcmp(cmd, "pwd") == 0)
// 		return (1);
// 	else if (strcmp(cmd, "cd") == 0)
// 		return (1);
// 	else if (strcmp(cmd, "exit") == 0)
// 		return (2);
// 	else if (strcmp(cmd, "export") == 0)
// 		return (1);
// 	else if (strcmp(cmd, "echo") == 0)
// 		return (1);
// 	else if (strcmp(cmd, "env") == 0)
// 		return (1);
// 	else
// 		return (0);
// }

static enum e_pars	check_cmd(enum e_pars token, char *str, enum e_token *ID)
{
	if (token == N_SORTED)
	{
		token = check_quoted(str, ID);
		if (token == N_SORTED)
			token = TXT;
	}
	return (token);
}

static void    give_cmd(t_pars *pars)
{
    int i;

    i = 0;
    while (pars != NULL)
    {
        if(is_redirect(pars->token))
        {
            pars->next->token = ARG;
            pars = pars->next;
        }
        if(pars->token == PIPE)
            give_cmd(pars->next);
        if (i == 0 && pars->token == N_SORTED)
        {
            pars->token = CMD;
            i = 1;
        }
        else
            check_cmd(pars->token, pars->str, pars->ID);
        if (pars->token == 0)
            pars->token = TXT;
        pars = pars->next;
    }
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
		// (*pars)->token = check_cmd((*pars)->token, (*pars)->str, (*pars)->ID, env);
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
    give_cmd(*pars);
    (*pars) = tmp;
}
