/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:34:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/05 16:39:57 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	*find_path(char **envp)
{
	int	i;
	int	no_path;

	i = 0;
	no_path = 0;
	if (!envp[0])
	{
		msg(NO_PATH);
		exit(1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 6) != NULL)
			no_path = 1;
		i++;
	}
	if (no_path == 0)
	{
		msg(NO_PATH);
		exit(1);
	}
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}*/

char	*get_cmd(char **paths, char *cmd)
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
}

void    dup_cmd(t_pars **pars, t_pipe *file)
{
	t_pars  *tmp;
	int     i;
	
	tmp = *pars;
	i = 0;
	file->cmd_to_exec = malloc(sizeof(char *) * (file->cmd_nb + 1));
	while ((*pars) != NULL)
	{
		if ((*pars)->token == CMD)
		{
			file->cmd_to_exec[i] = ft_strdup((*pars)->str);
			i++;
		}
		*pars = (*pars)->next;
	}
	file->cmd_to_exec[i] = 0;
	*pars = tmp;
}


void    is_cmd(t_pars **pars, t_pipe *file, char **envp)
{
	t_pars *tmp;
	
	tmp = *pars;
	file->cmd_nb = 0;
	file->paths = find_path(envp);
	file->cmd_paths = ft_split(file->paths, ':');
	//while ((*pars) != NULL && (*pars)->token != R_OUTPUT && (*pars)->token != R_DOUTPUT)
	while ((*pars) != NULL)
	{
		file->cmd_args = ft_split((*pars)->str, ' ');
		file->cmd = get_cmd(file->cmd_paths, file->cmd_args[0]);
		if (!file->cmd)
			//continue ;
			printf("%s is not a command\n", (*pars)->str);
		else
		{
			(*pars)->token = CMD;
			file->cmd_nb += 1;
			/*if ((*pars)->next->str[0] == '-')
				file->cmd_args[0] = (*pars)->next->str;
			else
				file->cmd_args[0]= NULL;*/
			
			printf("%s is a valid command\n", (*pars)->str);
			//break;
		}
		//printf(" and token equal : %u\n", (*pars)->token);
		*pars = (*pars)->next;
	}
	//printf("command number = %d\n", file->cmd_nb);
	*pars = tmp;
	if (file->cmd_nb > 0)
		dup_cmd(pars, file);
	int a = 0;
	while (file->cmd_to_exec[a] != 0)
	{
		printf("TA %d CMD EST = %s\n", a, file->cmd_to_exec[a]);
		a++;
	}
	return ;
}
