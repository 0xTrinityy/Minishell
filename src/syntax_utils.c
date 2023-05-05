/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:45:27 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/05 09:48:56 by luciefer         ###   ########.fr       */
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

static char	*ft_exist(char *tmp, char *str, char *env, char *exp)
{
	int	size;
	int	i;

	i = 0;
	size = (ft_strlen(str) - ft_strlen(exp))
		+ (ft_strlen(env) - ft_strlen(exp) - 1);
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		exit (0);
	while (str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	ft_strlcat(tmp, ft_strchr(env, '='),
		ft_strlen(env) + ft_strlen(str));
	i += ((int)ft_strlen(exp) + 1);
	ft_strlcat(tmp, str + i, ft_strlen(str) + ft_strlen(env));
	return (tmp);
}

static char	*replace_expand(char *str, char **env, char *exp)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = 0;
	while (env[j])
	{
		if (ft_strnstr(env[j], exp, ft_strlen(exp)) != NULL
			&& env[j][ft_strlen(exp)] == '=')
			return (ft_exist(tmp, str, env[j], exp));
		else
			j++;
	}
	j = 0;
	if ((ft_strlen(str) - ft_strlen(exp) - 1) == 0)
		return ("");
	tmp = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(exp) - 1) + 1);
	ft_strcpy_dollar(tmp, str);
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
	pars->str = tmp;
	pars = new_id(pars);
	return (-1);
}

void	replace_dollar(t_pars *pars, char **env, char *tmp)
{
	int		i;
	int		u;

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
			tmp = is_expand(pars, tmp, i);
			pars->str = replace_expand(pars->str, env, tmp);
			if (!pars->str[0])
				break ;
			pars = new_id(pars);
			i = -1;
		}
		i++;
	}
	pars->token = ARG;
	return ;
}