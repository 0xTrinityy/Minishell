/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:33:45 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/03 12:01:29 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	first_child(t_pipe *file, t_pars **pars, char **envp)
{
	t_pars *tmp;
	int count;
	//dup2(data.pipe[1], 1);
	//close(data.pipe[0]);
	//dup2(data.infile, 0);
	dup2(file->infile, 0);
	//close (0);
	dup2(file->outfile, 1);
	//printf("THE OUTFILE VALUE = %d\n", file->outfile);
	//close (1);
	count = 0 ;
	tmp = *pars;
	while (*pars != NULL) 
	{
		if ((*pars)->token == CMD)
		{
			count = 1;
			break;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if (count == 0)
	{
		msg_error(ERR_CMD, file);
		exit (1);
	}
	printf("file CMD =  %s file args = %s\n", file->cmd_to_exec[0], file->cmd_args[0]);
	printf(" INFILE = %d and OUTFILE = %d\n", file->infile, file->outfile); 
	execve(file->cmd, file->cmd_args, envp);
	/*data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		close_all(&data);
		parent_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	/*close(data.pipe[1]);
	close_all(&data);
	while (t)
	execve(data.cmd, data.cmd_args, envp);
	error_free(&data);
	free(data.cmd);
}*/