/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:02:21 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/25 13:57:55 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_data *data, t_pipe *file)
{
	int i;
	i = 0;
	if (!data->env[i])
		msg(NO_PATH);
	while (data->env[i] != 0)
	{
		printf("%s", data->env[i]);
		printf("\n");
		i++;
	}
	return ;
}