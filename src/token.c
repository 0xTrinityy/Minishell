#include "../includes/minishell.h"

static enum e_pars	check_pipes(enum e_pars token, char *str, enum e_token *ID)
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
		if (str[0] == '>' && str[1] != '>')
			token = R_OUTPUT;
		else if (str[0] == '<' && str[1] != '<')
			token = R_INPUT;
		return (token);
	}
	while (str[i] == '>' && str[i + 1] == '>' && str[i] && str[i + 1])
	{
		i++;
		token = R_DOUTPUT;
	}
	while (str[i] == '<' && str[i + 1] == '<' && str[i] && str[i + 1])
	{
		i++;
		token = R_DINPUT;
	}
	return (token);
}

static void	give_cmd(t_pars *pars, int i)
{
	while (pars != NULL)
	{
		if (is_redirect(pars->token))
		{
			pars = pars->next;
			if (pars == NULL)
				return ;
			if (pars->token == 0)
				pars->token = ARG;
		}
		if (pars->token == PIPE)
			give_cmd(pars->next, 0);
		if (i == 0 && pars->token == N_SORTED)
		{
			pars->token = CMD;
			i = 1;
		}
		if (pars->token == 0)
			pars->token = ARG;
		pars = pars->next;
	}
}

void	put_token(t_pars **pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = (*pars);
	while ((*pars) != NULL)
	{
		(*pars)->token = check_pipes((*pars)->token, (*pars)->str, (*pars)->id);
		(*pars)->token = check_redirect((*pars)->token, (*pars)->str);
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	give_cmd(*pars, 0);
	(*pars) = tmp;
}
