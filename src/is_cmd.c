/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:34:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/24 13:58:09 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
    while (*paths != NULL)
    {
        if (access(cmd, F_OK) == 0) 
        {
            return cmd;
        }
        char *tmp = ft_strjoin(*paths, "/");
        char *command = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(command, F_OK) == 0) 
        {
            return command;
		}
        free(command);
        paths++;
    }

    return NULL;
}
