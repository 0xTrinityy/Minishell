/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:23:00 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 11:19:38 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	ft_pwd(t_pipe *file)
{
	char	*path;

	g_global = 1;
	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_putstr_fd("error pwd\n", file->outfile);
	ft_putstr_fd(path, file->outfile);
	ft_putstr_fd("\n", file->outfile);
	free(path);
	g_global = 0;
}
