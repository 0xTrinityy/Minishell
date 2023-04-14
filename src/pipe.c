/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:08 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/14 13:40:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void    trimmed_cmd()
{



}

void    trimmed_args()
{



}

int     pipe()
{


}

void	end_main(t_pipe data, int argc, char **envp, char **argv)
{
	int	i;

	i = 0;
	while (data.pidx < data.cmd_nb)
	{
		multiple_cmd(data, argv, envp);
		data.pidx++;
	}
	close_pipes(&data);
	while (i < data.cmd_nb)
	{
		waitpid(data.pid[i], NULL, 0);
		i++;
	}
	parent_free(&data, argc);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;

	if (argc - 1 < 4)
		msg_error(ERR_INPUT, &data);
	is_heredoc(argv, &data);
	if (data.infile < 0)
		infile_error(ERR_INFILE, &data);
	data.outfile = out_file(argc, argv, &data);
	if (data.outfile < 0)
		msg_error(ERR_OUTFILE, &data);
	data.pipe_nb = 2 * ((argc - 3 - data.doc) - 1);
	data.pipe = malloc(sizeof(int *) * data.pipe_nb);
	if (pipe(data.pipe) < 0)
		msg_error(ERR_PIPE, &data);
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	new_pipe(&data, argc);
	data.pid = malloc(sizeof(pid_t) * (data.cmd_nb));
	if (!data.pid)
		pid_err(&data, argc);
	end_main(data, argc, envp, argv);
	return (0);
}