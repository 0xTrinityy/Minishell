/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_replace_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:45:27 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 15:23:23 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	ft_exist(char *tmp, t_pars *pars, char *env, char *exp)
{
	int	size;
	int	i;

	i = 0;
	size = (ft_strlen(pars->str) - ft_strlen(exp)) + (ft_strlen(env)
			- ft_strlen(exp) - 1);
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		exit(0);
	while (pars->str[i] != '$')
	{
		tmp[i] = pars->str[i];
		i++;
	}
	tmp[i] = 0;
	ft_strlcat(tmp, ft_strchr(env, '=') + 1, ft_strlen(env)
		+ ft_strlen(pars->str));
	i += ((int)ft_strlen(exp) + 1);
	ft_strlcat(tmp, pars->str + i, ft_strlen(pars->str) + ft_strlen(env));
	free(pars->str);
	pars->str = tmp;
}

static void	replace_value(t_pars **pars, char **env, char *exp)
{
	int		j;
	char	*tmp;

	tmp = 0;
	if(find_env(pars, tmp, env, exp))
        return ;
	j = 0;
	if ((ft_strlen((*pars)->str) - ft_strlen(exp) - 1) == 0)
	{
		free((*pars)->str);
		(*pars)->str = malloc(sizeof(char) * 1);
		if (!(*pars)->str)
			return ;
		(*pars)->str[0] = 0;
		return ;
	}
	tmp = malloc(sizeof(char) * (ft_strlen((*pars)->str) - ft_strlen(exp) - 1)
			+ 1);
	ft_strcpy_dollar(tmp, (*pars)->str);
	j += (int)ft_strlen(exp) + 1;
	if ((*pars)->str[j])
		ft_strlcat(tmp, (*pars)->str + j, ft_strlen((*pars)->str + j) + 1);
	free((*pars)->str);
	(*pars)->str = tmp;
}

int	check_dote(t_pars *pars, int i)
{
	char	*tmp;
	char	*nb;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(pars->str) + 3));
	while (j < i)
	{
		tmp[j] = pars->str[j];
		j++;
	}
	i += 2;
	tmp[j] = 0;
	nb = ft_itoa(g_global);
	ft_strlcat(tmp, nb, ft_strlen(pars->str) + 3);
	free(nb);
	if (pars->str[i])
		ft_strlcat(tmp, pars->str + i, ft_strlen(pars->str));
	free(pars->str);
	pars->str = tmp;
	pars = new_id(pars);
	return (-1);
}

t_pars	*find_dollar(t_pars *pars, char **env, char *tmp)
{
	int	i;
	int	u;

	i = 0;
	while (pars->str[i])
	{
		u = 0;
		if (pars->id[i] == DOLLAR && pars->str[i + 1] == '?')
			i = check_dote(pars, i);
		else if (pars->id[i] == DOLLAR)
		{
			i++;
			tmp = is_expand(pars, tmp, i);
			replace_value(&pars, env, tmp);
			free(tmp);
			if (!pars->str[0])
				break ;
			pars = new_id(pars);
			i = -1;
		}
		i++;
	}
	return (pars);
}

void	replace_dollar(t_pars *pars, char **env, char *tmp)
{
	int	i;

	i = 0;
	if (pars->token == TXT_D || (pars->token == CMD && (pars->id[0] == D_QUOTE
				|| pars->id[0] == S_QUOTE)))
	{
		del_quote(pars);
	}
	pars = find_dollar(pars, env, tmp);
	if (pars->token == CMD)
		check_cmd_valid(pars);
	if (pars->token == TXT || pars->token == TXT_D || pars->token == EXPAND)
		pars->token = ARG;
	return ;
}
