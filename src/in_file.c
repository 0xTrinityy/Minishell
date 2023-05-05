/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:47:50 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/03 19:31:01 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//L'OFFICIEL

static int     infile_nb(t_pars **pars)
{
	int     count;
	t_pars  *tmp;
	
	count = 0;
	tmp = *pars;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_INPUT || (*pars)->token == R_DINPUT)
			count++;
		*pars = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}

/*
static void    file_or_std(t_pars **pars, t_pipe *file)
{
	char    *tmp;
	t_pars  *tmp1;
	int     flag;

	tmp1 = *pars;
	flag = 0;
	tmp = NULL;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == TXT)
		{
			tmp = (*pars)->str;
			flag = 1;
			break;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp1;
	if (flag == 1)
		file->infile = open(tmp, O_RDONLY);
	else
		file->infile = 0;
	//free(tmp);
	//free(tmp1);
	return ;
}*/

void    infile_read(t_pipe *file, t_pars **pars)
{
	char    *tmp;
	t_pars  *tmp1;
	int     flag;
	int     count;
	
	tmp1 = *pars;
	flag = 0;
	count = infile_nb(pars);
	tmp = NULL;
	while ((*pars) != NULL && count > 0)
	{
		if ((*pars)->token == R_INPUT)
		{
			tmp = (*pars)->next->str;
			flag = 1;
			file->infile = open(tmp, O_RDONLY);
			if (file->infile < 0)
				msg_error(ERR_INFILE, file);
			count--;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp1;
	file->doc = 0;
	/*if (flag == 1)
		file->infile = open(tmp, O_RDONLY);
	else*/
	if (flag == 0)
		file->infile = 0;
	if (file->infile < 0)
		infile_error(ERR_INFILE, file);
	free(tmp);
	free(tmp1);
}