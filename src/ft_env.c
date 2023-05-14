/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:02:21 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/14 17:59:24 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_env(t_pipe *data)
{
	int     i;
	printf("DEBUGGGGGG");
	i = 0;
	if (!data->env[i])
		msg(NO_PATH);
	while(data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return ;
}