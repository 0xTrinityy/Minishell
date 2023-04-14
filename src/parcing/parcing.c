/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:45:22 by luciefer          #+#    #+#             */
/*   Updated: 2023/04/14 13:07:07 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	char_ID(char *str, enum e_token *ID)
{
	int	i;

	i = 0;
	ID = (enum e_token *) malloc(sizeof(enum e_token) * ft_strlen(str) + 1);
	if (!ID)
		ft_free_all();
	while (str[i])
	{
		if (str[i] == '\"')
			ID[i] = D_QUOTE;
		else if (str[i] == '\'')
			ID[i] = S_QUOTE;
		else if (str[i] == '|')
			ID[i] = PIPE_C;
		else if (str[i] == '<' || str[i] == '>')
			ID[i] = REDIRECT;
		else if (str[i] == '$')
			ID[i] = DOLLAR;
		else if (str[i] == ' ' || str[i] == '	' || str[i] == '\n')
			ID[i] = IFS;
		else
			ID[i] = ALPHA_NUM;
		i++;
	}
	ID[i] = FINISH;
}

int	ft_parcing(t_list *pars, char *str, char **env)
{
	enum e_token	*ID;

	char_ID(str, ID);
	get_word(pars, str, ID);
	replace_expand(pars, env);
	syntax_analyser();
}
