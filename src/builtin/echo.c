/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:49:20 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/14 14:05:47 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ok refaire echo en gerant le cas d'erreur "echo -n -n "
//ou encore "echo -n bonjour -n"

size_t	ft_strlen(const char *s)
int	n_option(char *str)
{
	if (ft_strlen(str) != 2)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(char **str)
{
	int	i;

	i = 1;
	if (!str[1])
	{
		write(fd, &s[i], 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (n_option(str[1]))
		i++;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_option(str[1]))
		ft_putstr_fd("\n", 1);
	return (0);
}

int	n_option(t_args *data)
{
	if (ft_strlen(data->argv[1]) != 2)
		return (0);
	if (data->argv[1][0] == '-' && data->argv[1][1] == 'n')
		return (1);
	else
		return (0);
}

int	ft_echo(t_args *data)
{
	int i;

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
