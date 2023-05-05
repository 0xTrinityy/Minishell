/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:42:43 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/01 18:21:30 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	neww(int infile, int outfile)
{
	dup2(infile, 0);
	dup2(outfile, 1);
}

void	multiple_cmd(t_pipe file, char **envp)
{
	int     i;
	
	i = 0;
	//printf("DANS LE CHILD, PIDX vaut = %d\n", file.pidx);
	file.pid[file.pidx] = fork();
	if (!file.pid[file.pidx])
	{
		if (file.pidx == 0)
			neww(file.infile, file.pipe[1]);
		else if (file.pidx == file.cmd_nb - 1)
			neww(file.pipe[2 * file.pidx - 2], file.outfile);
		else
			neww(file.pipe[2 * file.pidx - 2], file.pipe[2 * file.pidx + 1]);
		close_pipes(&file);
		file.cmd_args = ft_split(file.cmd_to_exec[file.pidx], ' ');
		file.cmd = get_cmd(file.cmd_paths, file.cmd_args[0]);
		//printf("")
		if (!file.cmd)
		{
			/*child_free1(&file);
			close_all1(&file);
			parent_free1(&file);
			msg(ERR_CMD);*/
			exit(1);
		}
		//printf("La commande qui va etre exec = %s\n\n", file.cmd);
		execve(file.cmd, file.cmd_args, envp);
		printf("EXEC FAIL\n");
		//error_free(&file);
		///free(file.cmd);
	}
}