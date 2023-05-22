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

extern int  g_global;

void    ft_pwd(void)
{
    char    *path;

    g_global = 1;
    path = getcwd(NULL, 0); 
    if (path == NULL)
        printf("error pwd\n");
    printf("%s\n", path);
    free (path);
    g_global = 0;
}
