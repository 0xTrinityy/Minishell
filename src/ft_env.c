/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:02:21 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 13:50:21 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_data *data, t_pipe *file)
{
	int	i;

	i = 0;
	if (!data->env[i])
		msg(NO_PATH, 1);
	while (data->env[i] != 0)
	{
		ft_putstr_fd(data->env[i], file->outfile);
		ft_putstr_fd("\n", file->outfile);
		i++;
	}
	return ;
}
