/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:53:28 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/06 11:02:45 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths != NULL)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}*/

char    **tema_larg(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int     i;
	char    **arg;
	
	
	arg = malloc(sizeof(char*) * 20000);
	tmp = *pars;
	i = 0;
	arg[i] = file->cmd_to_exec[0];
	i++;
	//*pars = (*pars)->next;
	//printf("ELEMENT %s\n", (*pars)->str);
	while ((*pars) != NULL && ((*pars)->token != PIPE && (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT))
	{
		if((*pars)->token != CMD)
		{
			arg[i] = (*pars)->str;
			//printf("L'arg vaut = %s\n", arg[i]);
			i++;
		}
		(*pars) = (*pars)->next;
	}
	(*pars) = tmp;
	arg[i] = 0;
	return (arg);
}

static void	first_child(t_pipe *file, t_pars **pars, char **envp)
{
	t_pars *tmp;
	int count;
	
	dup2(file->infile, 0);
	dup2(file->outfile, 1);
	count = 0 ;
	tmp = *pars;
	//printf("PARS STR = %s\n", (*pars)->str);
	while (*pars != NULL && file->cmd == NULL && ((*pars)->token != R_OUTPUT || (*pars)->token != R_DOUTPUT )) 
	{
		if ((*pars)->token == CMD)
		{
			count = 1;
			if ((*pars)->next->str != NULL)
				file->cmd_args = tema_larg(pars, file);
			else
			{
				file->cmd_args[0] = file->cmd_to_exec[0];
				file->cmd_args[1] = 0;
			}
			//printf("cmd arg = %s\n", file->cmd_args[0]);
			//printf("cmd arg = %s\n", file->cmd_args[1]);
			file->cmd = get_cmd(file->cmd_paths, file->cmd_to_exec[0]);
			//printf("cmd = %s\n", file->cmd);
			break;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if (count == 0 && file->cmd == NULL)
	{
		msg_error(ERR_CMD, file);
	}
	//printf("cmd arg 2 = %s\n", file->cmd_args[0]);
	//printf("cmd arg 2 = %s\n", file->cmd_args[1]);
	execve(file->cmd, file->cmd_args, envp);
}

void    one_cmd(t_pipe *file, t_pars **pars, char **envp)
{	
	redirect_hdoc(pars, file);
	is_heredoc(file, pars);
	file->outfile = 1;
	out_read_v2(file, pars);
	file->cmd_args = NULL;
	file->pidx = fork();
	printf("INFILE = %d\n", file->infile);
	printf("OUTFILE = %d\n", file->outfile);
	//printf("PARS STR = %p\n", &(*pars)->str);
	if (file->pidx == 0)
	{
		first_child(file, pars, envp);
		//close_pipes(file);
	}
	waitpid(file->pidx, NULL, 0);
	parent_free(file);
	return ;
}
