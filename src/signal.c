/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:44:31 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/31 16:39:48 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	siginthandler(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global = 130;
}

void	siginthandler_fork(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global = 131;
}

void	siginthandler_2(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	g_global = 130;
}
