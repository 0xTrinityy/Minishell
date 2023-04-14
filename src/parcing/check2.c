/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:41:58 by luciefer          #+#    #+#             */
/*   Updated: 2023/04/14 12:54:08 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd(t_list *new, char *str, enum e_token *ID)
{
	int	i;

	i = 0;
	while (ID[i] == ALPHA_NUM && ID[i] != FINISH)
		i++;
	if (i == 0)
		return (0);
	new->str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ID[i] == ALPHA_NUM && ID[i] != FINISH)
	{
		new->str[i] = str[i];
		i++;
	}
	if (cmd_comp(new->str))
	{
		new->e_pars = CMD;
		return (1);
	}
	else
	{
		new->e_pars = CMD;
		return (1);
	}
}

void	is_dollar(t-list *new, char *str, enum e_token *ID)
{
	int	i;

	i = 1;
	while (ID[i] != IFS && ID[i] != FINISH)
		i++;
	new->str = malloc(sizeof(char) * i);
	if (!new->str)
		ft_free_all();
	i = 1;
	while (ID[i] != IFS && ID[i] != FINISH)
	{
		new->str[i - 1] = str[i];
		i++;
	}
	new->e_pars = EXPAND;
}

void	is_expand(t_list *new, char *str, enum e_token *ID)
{
	int	i;

	i = 0;
	if (ID[0] == PIPE || ID[0] == REDIRECT)
	{
		new->str = malloc(sizeof(char) * 2);
		if (!new->str)
			ft_free_all();
		if (ID[0] == REDIRECT)
		{
			if (str[0] == '<')
				new->str[0] = '<';
			else
				new->str[0] = '>';
			new->e_pars = REDIRECT_TMP;
			return ;
		}
		new->str[0] = '|';
		new->e_pars = PIPE;
		return ;
	}
	else
		is_dollar(new, str, ID);
}

int	cmd_comp(char *cmd)
{
	if(strcmp(cmd, "unset") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else
		return (0);
}

