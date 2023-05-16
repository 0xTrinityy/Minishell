/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:23:00 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/15 18:52:28 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static char	*find_path_pwd(char **env)
{
	while (ft_strncmp("PWD", *env, 3))
		env++;
	return (*env + 4);
}

void    ft_pwd(t_data *data)
{
    char    *path;

    path = find_path_pwd(data->env);
    printf("%s", path);
}