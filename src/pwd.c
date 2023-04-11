/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:12 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/11 16:31:31 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PWD", *envp, 3))
		envp++;
	return (*envp + 4);
}

void    ft_pwd(char **envp)
{
    char    *path;

    path = find_path(envp);
    ft_putstr_fd(path, 1);
}