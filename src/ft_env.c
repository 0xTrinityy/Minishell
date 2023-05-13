/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:02:21 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/13 08:13:21 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_env(t_pipe *file)
{
	int     i;
	//printf("DEBUGGGGGG");
	i = 0;
	if (file->env[i])
		msg(NO_PATH);
	while(file->env[i])
	{
		printf("%s\n", file->env[i]);
		i++;
	}
	return ;
}