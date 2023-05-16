/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:39:26 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/16 11:54:05 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	is_arg(t_pars *pars)
// {
// 	t_pars	*tmp;
// 	int		i;
//
// 	i = 0;
// 	tmp = pars;
// 	while (pars != NULL)
// 	{
// 		if (i == 2)
// 			break ;
// 		if (pars->token == ARG)
// 			i = 2;
// 		pars = pars->next;
// 		if (pars != NULL && pars->token == PIPE)
// 		return (1);
// 	else if (pars != NULL && is_redirect(pars->token))
// 		i = 0;
// 	pars = pars->next;
// }
// if (pars == NULL)
// 	i = 1;
// pars = tmp;
// if (i == 1)
// 	return (1);
// return (0);
// }

void	ft_strcpy_dollar(char *tmp, char *str)
{
    int	i;

    i = 0;
    while (str[i] != '$')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = 0;
}

int check_syntax_redirect(t_pars *pars, char **env)
{
    t_pars	*tmp;

    tmp = pars;
    if (pars->token == CMD)
    {
        pars = pars->next;
        while (pars->token == ARG)
            pars = pars->next;
        if (!is_redirect(pars->token))
            return (0);
        pars = pars->next;
        if (pars->token != ARG)
            return (0);
        pars = pars->next;
        if (pars != NULL && pars->token == PIPE)
            check_syntax(pars, env);
    }
    else if (is_redirect(pars->token))
    {
        if (!check_next(pars))
            return (0);
        pars = pars->next->next;
        if (pars != NULL && pars->token == CMD)
                pars = pars->next;
        while (pars != NULL && pars->token == ARG)
            pars = pars->next;
        if (pars != NULL && is_redirect(pars->token))
        {
            if(!check_syntax_redirect(pars, env))
                return (0);
        }
        if (pars != NULL && pars->token == PIPE)
            check_syntax(pars->next, env);
        pars = tmp;
    }
    return (1);
}

t_pars	*new_id(t_pars *pars)
{
    free(pars->ID);
    pars->ID = (enum e_token *) malloc(sizeof(enum e_token)
                                       * (ft_strlen(pars->str) + 1));
    put_id(pars->str, pars->ID);
    return (pars);
}

char	*is_expand(t_pars *pars, char *tmp, int i)
{
    int	j;
    int	u;

    u = 0;
    j = i;
    while ((pars->str[j] >= '0' && pars->str[j] <= '9')
        || (pars->str[j] >= 'a' && pars->str[j] <= 'z')
        || (pars->str[j] >= 'A' && pars->str[j] <= 'Z')
        || pars->str[j] == '_')
        j++;
    tmp = malloc(sizeof(char) * (j - i) + 1);
    if (!tmp)
        exit(malloc_sec2(pars, tmp));
    while (i < j)
        tmp[u++] = pars->str[i++];
    tmp[u] = 0;
    // printf("tmp: %s\n", tmp);
    return (tmp);
}
