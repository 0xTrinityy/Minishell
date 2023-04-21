/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:08 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/21 10:39:28 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void     redirect_infile(t_pars *data, t_pipe *file)
{
	t_pars *tmp;
	char    *in;
	int     size;
	
	size = 0;
	tmp = data;
	while (data->next != NULL)
	{
		if (data->token == R_INPUT)
		{
			data = data->next;
			size = ft_strlen(data->str);
			file->in_str = malloc(sizeof(char) * (size * 1));
			size = 0;
			while (data->str[size] != '\0')
			{
				file->in_str[size] = data->str[size];
				size++;
			}
			file->in_str[size] = '\0';
		}
	}
	data = tmp;
	return ;
}

void     redirect_outfile(t_pars *data, t_pipe *file)
{
	t_pars *tmp;
	char    *in;
	int     size;
	
	size = 0;
	tmp = data;
	while (data->next != NULL)
	{
		if (data->token == R_OUTPUT)
		{
			data = data->next;
			size = ft_strlen(data->str);
			file->out_str = malloc(sizeof(char) * (size * 1));
			size = 0;
			while (data->str[size] != '\0')
			{
				file->out_str[size] = data->str[size];
				size++;
			}
			file->out_str[size] = '\0';
		}
	}
	data = tmp;
	return ;
}

void    redirect_hdoc(t_pars *data, t_pipe *file)
{
		t_pars *tmp;
	char    *in;
	int     size;
	
	size = 0;
	tmp = data;
	file->doc = 0;
	while (data->next != NULL)
	{
		if (data->token == R_DINPUT)
		{
			file->doc += 1;
			file->limit = ft_strdup(data->next->str);
		}
	}
	data = tmp;
	return ;
}

void	end_main(t_pipe file, char **envp)
{
	int	i;

	i = 0;
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
	parent_free(&file);
}

int	execution(t_pars *data, char **envp)
{
	t_pipe	file;

	is_heredoc(&file);
	if (file.infile < 0)
		infile_error(ERR_INFILE, &data);
	file.outfile = out_file(&data);
	if (file.outfile < 0)
		msg_error(ERR_OUTFILE, &data);
	file.pipe_nb = 2 * 0; //nombre de pipe dans la str
	file.pipe = malloc(sizeof(int *) * file.pipe_nb);
	if (pipe(file.pipe) < 0)
		msg_error(ERR_PIPE, &data);
	file.paths = find_path(envp);
	file.cmd_paths = ft_split(file.paths, ':');
	new_pipe(&data);
	file.pid = malloc(sizeof(pid_t) * (file.cmd_nb));
	if (!file.pid)
		pid_err(&file);
	end_main(file, envp);
	return (0);
}
