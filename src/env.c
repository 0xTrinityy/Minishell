/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:05 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/06 19:32:19 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void    ft_env(t_args *data)
{
	int     i;
	
	i = 0;
	if (!data->envp[i])
		msg(NO_PATH);
	while(data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return ;
}
