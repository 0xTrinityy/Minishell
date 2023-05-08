/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:34:13 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:14:08 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect(enum e_pars token)
{
	if (token == R_INPUT)
		return (1);
	else if (token == R_OUTPUT)
		return (1);
	else if (token == R_DINPUT)
		return (1);
	else if (token == R_DOUTPUT)
		return (1);
	else
		return (0);
}

t_pars	*ft_lstlast_(t_pars *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	put_id(char *str, enum e_token *ID)
{
	int	i;

	i = 0;
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
	return ;
}
