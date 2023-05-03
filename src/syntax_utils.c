/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:45:27 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/03 18:53:21 by luciefer         ###   ########.fr       */
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
	pars->ID = (enum e_token *) malloc(sizeof(enum e_token)
			* (ft_strlen(tmp) + 1));
	if (!pars->ID)
	{
		free(pars->ID);
		ft_free_all();
	}
	put_id(tmp, pars->ID);
	pars->str = tmp;
	pars->token = ARG;
	return ;
}

static char	*replace_expand(char *str, char **env, char *exp)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], exp, ft_strlen(exp)) != NULL
				&& env[i][ft_strlen(exp)] == '=')
		{
			size = (ft_strlen(str) - ft_strlen(exp))
				+ (ft_strlen(env[i]) - ft_strlen(exp) - 1);
			tmp = malloc(sizeof(char) * size);
			if (!tmp)
				exit (0);
			while (str[j] != '$')
			{
				tmp[j] = str[j];
				j++;
			}
			tmp[j] = 0;
			ft_strlcat(tmp, ft_strchr(env[i], '='),
					ft_strlen(env[i]) + ft_strlen(str));
			j += ((int)ft_strlen(exp) + 1);
			ft_strlcat(tmp, str + j, ft_strlen(str) + ft_strlen(env[i]));
			return (tmp);
		}
		else
			i++;
	}
	size = ft_strlen(str) - ft_strlen(exp) - 1;
	if (size == 0)
		return ("");
	tmp = malloc(sizeof(char) * (size) + 1);
	while (str[j] != '$')
	{
		tmp[j] = str[j];
		j++;
	}
	tmp[j] = 0;
	j += (int)ft_strlen(exp) + 1;
	if (str[j])
		ft_strlcat(str + j, tmp, ft_strlen(str + j));
	return (tmp);
}

int	check_dote(t_pars *pars, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(pars->str) + 2));
	while (j < i)
	{
		tmp[j] = pars->str [j];
		j++;
	}
	i += 2;
	tmp[j] = 0;
	ft_strlcat(tmp, ft_itoa(g_global), ft_strlen(pars->str) + 3);
	if (pars->str[i])
		ft_strlcat(tmp, pars->str + i, ft_strlen(pars->str));
	free(pars->ID);
	pars->str = tmp;
	pars->ID = (enum e_token *) malloc(sizeof(enum e_token) * (ft_strlen(pars->str) + 1));
	put_id(pars->str, pars->ID);
	return (0);
}

void	replace_dollar(t_pars *pars, char **env)
{
	int		i;
	int		j;
	int		u;
	char	*tmp;

	i = 0;
	if (pars->token == TXT_D)
		del_quote(pars);
	while (pars->str[i])
	{
		u = 0;
		if (pars->ID[i] == DOLLAR && pars->str[i + 1] == '?')
			i = check_dote(pars, i);
		else if (pars->ID[i] == DOLLAR)
		{
			i++;
			j = i;
			while ((pars->str[j] >= '0' && pars->str[j] <= '9')
					|| (pars->str[j] >= 'a' && pars->str[j] <= 'z')
					|| (pars->str[j] >= 'A' && pars->str[j] <= 'Z') || pars->str[j] == '_')
				j++;
			tmp = malloc(sizeof(char) * (j - i) + 1);
			while (i < j)
				tmp[u++] = pars->str[i++];
			tmp[u] = 0;
			pars->str = replace_expand(pars->str, env, tmp);
			if (pars->str[0])
			{
				free(pars->ID);
				pars->ID = (enum e_token *) malloc(sizeof(enum e_token) * (ft_strlen(pars->str) + 1));
				put_id(pars->str, pars->ID);
			}
			else
				break;
			i = 0;
		}
		else
			i++;
	}
	pars->token = ARG;
	return ;
}



