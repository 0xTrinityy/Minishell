/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:23:00 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/28 12:35:12 by tbelleng         ###   ########.fr       */
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

void	ft_pwd_mult(t_pipe *file)
{
	char	*path;

	(void)file;
	g_global = 1;
	path = getcwd(NULL, 0);
	if (path == NULL)
		printf("error pwd\n");
	printf("%s\n", path);
	free(path);
	g_global = 0;
}
