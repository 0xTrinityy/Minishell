/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:48:02 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/31 10:21:44 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_hdoc(t_pars **pars, t_pipe *file)
{
	t_pars	*tmp;
	int		size;

	size = 0;
	tmp = *pars;
	file->doc = 0;
	while ((*pars) != NULL)
	{
		if ((*pars)->token == R_DINPUT)
		{
			file->doc += 1;
			file->limit = ft_strdup((*pars)->next->str);
		}
		*pars = (*pars)->next;
	}
	*pars = tmp;
	return ;
}

void	read_doc(t_pipe *file)
{
	int		fd;
	int		size;
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
	dup2(file->infile, 0);
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
}

int	pipe_count(t_pars **pars)
{
	int		count;
	t_pars	*tmp;

	count = 0;
	tmp = *pars;
	while (*pars != NULL)
	{
		if ((*pars)->token == PIPE)
			count++;
		*pars = (*pars)->next;
	}
	*pars = tmp;
	return (count);
}
