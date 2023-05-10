/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:48:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/09 16:01:38 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    redirect_hdoc(t_pars **pars, t_pipe *file)
{
	t_pars *tmp;
	int     size;
	
	size = 0;
	tmp = *pars;
	file->doc = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_DINPUT)
		{
			file->doc += 1;
			file->limit = ft_strdup((*pars)->next->str);
			//printf("limit = %s\n", file->limit);
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	//free(tmp);
	return ;
}

void	read_doc(t_pipe *file)
{
	int		fd;
	int     size;
	char	*buffer;

	fd = open(".here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0000644);
	if (fd < 0)
		msg_error(ERR_HEREDOC, file);
	size = ft_strlen(file->limit);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, file->limit, size))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	file->infile = open(".here_doc", O_RDONLY);
}

void	is_heredoc(t_pipe *file, t_pars **pars)
{
	int	a;

	a = 0;
	file->pidx = 0;
	if (file->doc == 1)
		read_doc(file);
	else
	{
		infile_read(file, pars);
	}
	//printf("is there an hdoc = %d\n", file->doc);
}

int    pipe_count(t_pars **pars)
{
	int     count;
	t_pars  *tmp;
	
	count = 0;
	tmp = *pars;
	while(*pars != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		*pars = (*pars)->next;
	}
	*pars = tmp;
	count = count * 2;
	return (count);
}


void	new_pipe(t_pipe *file)
{
	int	i;

	i = 0;
	while (i < file->cmd_nb)
	{
		if (pipe(file->pipe + (2 * i)) < 0)
			parent_free(file);
		i++;
	}
}

/*
int	execution(t_pars **pars, char **envp)
{
	t_pipe	file;
	int     i;

	i = 0;
	//file.pidx = 0;
	is_cmd(pars, &file, envp);
	redirect_hdoc(pars, &file);
	is_heredoc(&file, pars);
	file.outfile = 1;
	out_read_v2(&file, pars);
	//printf("le nombre de pipe est de %d\n\n\n", file.pipe_nb);
	if (file.cmd_nb > 1)
	{
		file.pipe_nb = pipe_count(pars);
		file.pipe = malloc(sizeof(int *) * file.pipe_nb);
		if (pipe(file.pipe) < 0)
			msg_error(ERR_PIPE, &file);
		new_pipe(&file);	
	//printf("DEBUGGGGG\n");
		file.pid = malloc(sizeof(pid_t) * (file.cmd_nb));
		if (!file.pid)
			pid_err(&file);
	//printf("PIDX = %d et CMD_MB = %d\n", file.pidx, file.cmd_nb);
		while (file.pidx < file.cmd_nb)
		{
			multiple_cmd(file, envp);
			file.pidx++;
		}
		close_pipes(&file);
		while (i < file.cmd_nb)
		{
			waitpid(file.pid[i], NULL, 0);
			i++;
		}
	}
	else
	{
		if (pipe(file.pipe) < 0)
			msg_error(ERR_PIPE, &file);
		file.pidx = fork();
		printf("PID vaut %d\n", file.pidx);
		printf("avant d'exec, outfile = %d\n", file.outfile);
		if (file.pidx == 0)
		{
			first_child(&file, pars, envp);
			close_pipes(&file);
		}
	}
	printf("NB de commande = %d\n", file.cmd_nb);
	if (file.cmd_nb == 1)
	{
		waitpid(file.pidx, NULL, 0);
	}
	//parent_free(&file);
	if (file.doc == 1)
	{
		unlink(".here_doc");
		return (1);
	}
	return (0);
}


 //faire une fonction speciale si on a qu une seule commande
 //gerer sans qu on est d'outfile ou d'infile'
 
 */