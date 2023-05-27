/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:07:08 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 17:54:36 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_cmdd(t_pars **pars, t_pipe *file)
{
	t_pars	*tmp;
	int		i;

	tmp = *pars;
	i = 0;
	file->cmd_to_exec = malloc(sizeof(char *) * (file->cmd_nb + file->builtin
				+ 1));
	if (!file->cmd_to_exec)
		return ;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == CMD || (*pars)->token == BUILTIN)
		{
			file->cmd_to_exec[i] = ft_strdup((*pars)->str);
			i++;
		}
		*pars = (*pars)->next;
	}
	file->cmd_to_exec[i] = 0;
	*pars = tmp;
}

t_pars	*find_first_cmd(t_pars *pars)
{
	while (pars)
	{
		if (pars->token == CMD || pars->token == BUILTIN)
		{
			pars->doc = -1;
			pars->limiter = NULL;
			break ;
		}
		pars = pars->next;
	}
	return (pars);
}

t_pars	*find_previous_cmd(t_pars *pars)
{
	while (pars && pars->token != PIPE)
		pars = pars->prev;
	while (pars && pars->token != CMD && pars->token != BUILTIN)
		pars = pars->prev;
	return (pars);
}

void	set_doc(t_pipe *file, t_pars **pars)
{
	t_pars	*tmp;
	t_pars	*cmd;

	tmp = *pars;
	cmd = find_first_cmd(tmp);
	tmp = *pars;
	while (tmp)
	{
		if (tmp->token == R_DINPUT)
		{
			if (cmd)
			{
				cmd->doc = HEREDOC;
				file->doc = 1;
				cmd->limiter = tmp->next->str;
			}
			create_node_and_list(file, tmp->next->str);
			printf("node\n");
		}
		else if (tmp->token == R_INPUT && (cmd))
			cmd->doc = INFILE;
		if (tmp->token == PIPE)
			cmd = find_first_cmd(tmp->next);
		tmp = tmp->next;
	}
}

void	init_pars(t_pars *pars)
{
	while (pars)
	{
		pars->limiter = NULL;
		pars->doc = -1;
		pars = pars->next;
	}
}
