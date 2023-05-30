/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:22:55 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/27 16:44:10 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pars(t_pars **pars)
{
	t_pars	*tmp;

	while ((*pars) != NULL)
	{
		tmp = (*pars)->next;
		free((*pars)->id);
		free((*pars)->str);
		free(*pars);
		*pars = tmp;
	}
}

void	redirect_output(t_pipe *file, int *last, int nb_rd, t_pars *cmd)
{
	if (nb_rd == 0)
		file->infile = file->prev_pipes;
	if (*last == HEREDOC)
		file->infile = find_doc_fd(file->node, cmd->limiter);
}

void	creating_append(t_pars **pars, t_pipe *file, int *last)
{
	*last += 1;
	if (file->outfile != 1)
		close(file->outfile);
	file->outfile = open((*pars)->next->str,
			O_APPEND | O_CREAT | O_RDWR, 0000644);
	if (file->outfile < 0)
		msg_error(ERR_OUTFILE, file);
}
