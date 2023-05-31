/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:07:08 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 10:01:58 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			file->doc = 1;
			if (cmd)
			{
				cmd->doc = HEREDOC;
				cmd->limiter = tmp->next->str;
			}
			create_node_and_list(file, tmp->next->str);
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
