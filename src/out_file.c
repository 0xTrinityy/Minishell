/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:08:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/02 14:06:14 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int     redirect_nb(t_pars **pars)
{
	t_pars  *tmp;
	int count;
	
	tmp = *pars;
	count = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_OUTPUT || (*pars)->token == R_DOUTPUT)
			count++;
		*pars = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}


void	out_read_v2(t_pipe *file, t_pars **pars)
{
	t_pars  *tmp2;
	char    *tmp3;
	int     count;
	int     flag;
	
	tmp2 = *pars;
	tmp3 = NULL;
	flag = 0;
	count = redirect_nb(pars);
	while ((*pars) != NULL && count > 0)
	{
		if ((*pars)->token == R_OUTPUT)
		{
			tmp3 = (*pars)->next->str;
			file->outfile = open(tmp3, O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if (file->outfile < 0)
				msg_error(ERR_OUTFILE, file);
			count--;
			flag++;
		}
		else if ((*pars)->token == R_DOUTPUT)
		{	
			tmp3 = (*pars)->next->str;
			file->outfile = open(tmp3, O_TRUNC | O_CREAT | O_RDWR, 0000644);
			if (file->outfile < 0)
				msg_error(ERR_OUTFILE, file);
			count--;
			flag++;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp2;
	/*if (flag == 2)
		file->outfile = open(tmp3, O_APPEND | O_CREAT | O_RDWR, 0000644);
	else if (flag == 1)
		file->outfile = open(tmp3, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	else*/
	if (flag == 0)
		file->outfile = 1;
	if (file->outfile < 0)
		msg_error(ERR_OUTFILE, file);
	//free(tmp2);
	//free(tmp3);
}