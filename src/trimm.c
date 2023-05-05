/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:18:24 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/05 14:50:29 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **envp)
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
}

static char	*get_cmd(char **paths, char *cmd)
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

static void    dup_cmdd(t_pars **pars, t_pipe *file)
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

static void    is_a_cmd(t_pars **pars, t_pipe *file, char **envp)
{
	t_pars *tmp;

	tmp = *pars;
	file->cmd_nb = 0;
	file->paths = find_path(envp);
	file->cmd_paths = ft_split(file->paths, ':');
	while ((*pars) != NULL)
	{
		file->cmd = get_cmd(file->cmd_paths, (*pars)->str);
		if (file->cmd != NULL)
		{
			(*pars)->token = CMD;
			//printf("l input %s est bien une commande\n", (*pars)->str);
			file->cmd_nb += 1;
		}
		//else if (ft_strncmp(file))
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if (file->cmd_nb > 0)
		dup_cmdd(pars, file);
	//printf("CMD a la fin du TRIM = %s et nombre de commande = %d\n", file->cmd_to_exec[0], file->cmd_nb);
	return ;
}

int    trimm_exec(t_pars **pars, char **envp)
{
	t_pipe  file;
	
	is_a_cmd(pars, &file, envp);
	if (file.cmd_nb == 1)
	{
		one_cmd(&file, pars, envp);
		return (0);
	}
	if (file.cmd_nb > 1)
	{
		mult_cmd(&file, pars, envp);
		return (0);
	}
	if (file.cmd_nb <= 0)
	{
		msg_error(ERR_CMD, &file);
		exit (1);
	}
	return (0);
}







/*
static void    is_a_cmd(t_pars **pars, t_pipe *file, char **envp)
{
	t_pars *tmp;
	
	tmp = *pars;
	file->cmd_nb = 0;
	file->paths = find_path(envp);
	file->cmd_paths = ft_split(file->paths, ':');
	while ((*pars) != NULL)
	{
		file->cmd_args = ft_split((*pars)->str, ' ');
		file->cmd = get_cmd(file->cmd_paths, file->cmd_args[0]);
		if (file->cmd != NULL)
		{
			printf("LA CMD EST = %s\n", file->cmd);
			(*pars)->token = CMD;
			file->cmd_nb += 1;
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	if (file->cmd_nb > 0)
		dup_cmdd(pars, file);
	printf("CMD a la fin du TRIM = %s\n", file->cmd_to_exec[0]);
	return ;
}*/