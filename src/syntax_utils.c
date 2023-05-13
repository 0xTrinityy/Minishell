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
    // write(1, "ok\n", 3);
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
	ft_strlcat(tmp, ft_strchr(env, '=') + 1,
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

void    _lst_add_between(t_pars *new, t_pars *pars)
{
    if(!pars)
        new->next = NULL;
    else
    {
        new->prev = pars;
        new->next = pars->next;
    }
    if (!pars)
        pars = new;
    else
        pars->next = new;
}

void    recreate_pars(t_pars *pars, char *str, enum e_token *ID)
{
    int		i;
	t_pars	*tmp;
    int     u;

	i = 0;
    u = 0;
	while (str[i])
	{
		while (ID[i] == IFS && str[i])
			i++;
		if (ID[i] != FINISH)
		{
			tmp = get_word(&pars, str + i, ID + i, tmp);
			_lst_add_between(tmp, pars);
            if (pars->next != NULL)
                pars = pars->next;
		}
		i = i + ft_iter(str + i, ID + i);
	}
    while(pars->prev != NULL)
    {
        pars = pars->prev;
    }
}

void    check_cmd_valid(t_pars *pars)
{
    int i;
    char    **tab;

    i = 0;
    tab = 0;
    while (pars->str[i])
    {
        if (pars->ID[i] == IFS)
        {
            recreate_pars(pars, pars->str, pars->ID);
            pars = pars->next;
            pars->token = 1;
            i = 0;
        }
        i++;
    }
    return ;
}

void	replace_dollar(t_pars *pars, char **env, char *tmp)
{
	int		i;
	int		u;

	i = 0;
	if (pars->token == TXT_D)
		del_quote(pars);
    printf("%u\n", pars->token);
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
    if (pars->token == TXT || pars->token == TXT_D
              || pars->token == EXPAND)
    	pars->token = ARG;
    if (pars->token == CMD)
        check_cmd_valid(pars);
    return ;
}
