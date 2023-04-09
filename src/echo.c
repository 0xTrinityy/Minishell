/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:49:20 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/09 16:31:23 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
