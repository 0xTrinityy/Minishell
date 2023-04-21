/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:54:30 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/17 17:45:52 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	dup2(file->infile, 0);
}

void	is_heredoc(t_pipe *file)
{
	int	a;

	a = 0;
	file->pidx = 0;
	if (file->doc == 1)
		read_doc(file);
	else
	{
		file->doc = 0;
		file->infile = open(1, O_RDONLY);
	}
}