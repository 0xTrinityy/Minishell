/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:12 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/21 14:49:05 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] != '\0'
		&& (unsigned char)s2[i] != '\0' && i + 1 < n)
	{
		if (((unsigned char)s1[i]) != ((unsigned char)s2[i]))
			return (((unsigned char)s1[i]) - (unsigned char)s2[i]);
		i++;
	}
	return (((unsigned char)s1[i]) - (unsigned char)s2[i]);
}

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