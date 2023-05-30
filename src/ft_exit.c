/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:17:14 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 17:15:07 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define ULL_MAX 9223372036854775807

void	error_message_exit(char *str)
{
	(void)str;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

long long	ft_atoull(const char *str)
{
	int					neg;
	int					i;
	unsigned long long	res;

	res = 0;
	neg = 1;
	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		neg *= -1;
		if (str[i] == '-')
			i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if (res > ULL_MAX || (res > ULL_MAX && neg == -1))
			return (error_message_exit((char *)str), 2);
	}
	return ((long long)res * neg);
}

int	ft_isdigit_special(int arg)
{
	if ((arg >= '0' && arg <= '9') || arg == '-' || arg == '+')
		return (1);
	return (0);
}

static void	exit_end(t_pars **pars, t_pipe *file, t_data *data, t_pars *tmp)
{
	long long int	i;

	i = 0;
	(*pars) = (*pars)->next;
	while ((*pars)->str[i])
	{
		if (!ft_isdigit_special((*pars)->str[i]))
		{
			error_message_exit((*pars)->str);
			*pars = tmp;
			free_builtin(pars, file, data);
			exit(2);
		}
		i++;
	}
	i = ft_atoull((*pars)->str);
	*pars = tmp;
	free_builtin(pars, file, data);
	exit(i);
}

void	ft_exit_built(t_pars **pars, t_pipe *file, t_data *data)
{
	t_pars	*tmp;

	tmp = *pars;
	while ((*pars)->token != BUILTIN)
		(*pars) = (*pars)->next;
	if ((*pars)->next == NULL)
	{
		*pars = tmp;
		free_builtin(pars, file, data);
		exit(0);
	}
	if ((*pars)->next->next != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit_end(pars, file, data, tmp);
}
