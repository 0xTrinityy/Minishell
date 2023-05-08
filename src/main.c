/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/08 14:33:24 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_global;

void	ft_free(t_pars *pars)
{
	while (pars != NULL)
	{
		if (pars->str[0])
			free(pars->str);
		free(pars->ID);
		pars = pars->next;
	}
	return ;
}

// static char **cpy_env(char **envp)
// {
//     int i;
//     int j;
//
//     i = 0;
//     while(envp[i])
//         i++;
//     
// }

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
    int     i;
    // struct t_pipe   data;

	(void) ac;
	(void) av;
	pars = NULL;
    // data.env = cpy_env(envp);
	signal (SIGINT, &siginthandler);
	signal (SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (str)
	{
		add_history(str);
        i = ft_parcing(&pars, str, envp);
		if (i == 0)
			ft_putstr_fd("error\n", 1);
        else if (i == 1)
			trimm_exec(&pars, envp);
        printf("%s\n", strerror(g_global));
		free(str);
		ft_free(pars);
		str = readline("> ");
	}
}
