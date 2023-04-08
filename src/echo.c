/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:49:20 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/05 17:05:17 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int     n_option(t_args *data)
{
    if (ft_strlen(data->argv[1]) != 2)
        return (0);
    if (data->argv[1][0] == '-' && data->argv[1][1] == 'n')
        return (1);
    else
        return (0);
}

int    ft_echo(t_args *data)
{
    int     i;
    
    i = 1;
    if (!data->argv[i])
        return (0);
    if (n_option(data))
        i++;
    while (i < data->argc)
    {
        ft_putstr_fd(data->argv[i], 1);
        if (data->argv[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_option(data))
        ft_putstr_fd("\n", 1);
    return (1);   
}