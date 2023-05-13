/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:18:24 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 08:17:43 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//si on a un / ne pas verifier que c est une cmd et execute direct avec le path.


char	*find_path(char **envp)
{
	int	i;
	int	no_path;

	i = 0;
	no_path = 0;
	if (!envp[0])
	{
		msg(NO_PATH);
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
	}
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

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
		if ((*pars)->token == BUILTIN)
		{
			file->cmd_nb += 1;
			file->builtin += 1;
			break;
			(*pars) = (*pars)->next;
		}
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
	printf(" nombre de commande = %d\n", file->cmd_nb);
	return ;
}


t_pars* find_first_cmd(t_pars *pars)
{
	while (pars)
	{
		if (pars->token == CMD)
		{
			pars->doc = -1;
			pars->limiter = NULL;
			break ;
		}
		pars = pars->next;
	}
	return pars;
}

t_pars  *find_previous_cmd(t_pars *pars)
{
	while (pars && pars -> token != PIPE)
		pars = pars -> prev;
	while (pars && pars -> token != CMD)
		pars = pars -> prev;
	return pars;
}

void    set_doc(t_pipe *file, t_pars **pars)
{
	t_pars  *tmp;
	t_pars  *cmd;
	
	tmp = *pars;
	cmd = find_first_cmd(tmp);
	tmp = *pars;
	while (tmp)
	{
		if (tmp->token == R_DINPUT)
		{
			if (cmd)
			{
				cmd -> doc = HEREDOC;
				cmd->limiter = tmp->next->str;
			}
			create_node_and_list(file, tmp->next->str);
		}
		else if (tmp->token == R_INPUT)
		{
			if (cmd)
				cmd -> doc = INFILE;	
		}
		if (tmp->token == PIPE)
			cmd = find_first_cmd(tmp->next);
		tmp = tmp -> next;
	}
}

static void init_pars(t_pars *pars)
{
	while (pars)
	{
		pars->limiter = NULL;
		pars->doc = -1;
		pars = pars->next;
	}
}

int    trimm_exec(t_pars **pars, char **envp)
{
	t_pipe  file;
	
	ft_memset(&file, 0, sizeof(t_pipe));
	init_pars(*pars);
	is_a_cmd(pars, &file, envp);
	set_doc(&file, pars);
	here_doc(&file);
	if (file.cmd_nb == 1 )
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
