/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:12 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/20 15:02:54 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("OLDPWD", *envp, 6))
		envp++;
	return (*envp + 7);
}

void    pwd(char **envp)
{
    char    *path;

    path = find_path(envp);
    printf("%s\n", path);
}