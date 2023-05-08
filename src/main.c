/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/06 17:03:23 by luciefer         ###   ########.fr       */
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

static char **cpy_env(char **envp, t_pipe *data)
{
    int i;
    int j;

    i = 0;
    while(envp[i])
        i++;
    data->env = malloc(sizeof(char *) * i + 1);
    if(!data->env)
        return (0);
    i = 0;
    while(envp[i])
    {
        j = 0;
        while(envp[i][j])
            j++;
        data->env[i] = malloc(sizeof(char) * j + 1);
        if (!data->env[i])
            return (0);
        i++;
    }
    data->env[i] = 0;
    i = 0;
    while(envp[i])
    {
        data->env[i] = ft_strdup(envp[i]);
        i++;
    }
    return (data->env);
}


int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
    int     i;
    t_pipe   data;

	(void) ac;
	(void) av;
	pars = NULL;
    data.env = cpy_env(envp, &data);
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
			trimm_exec(&pars, data.env);
        printf("%s\n", strerror(g_global));
        printf("i = %d\n", i);
        printf("? = %d\n", g_global);
		free(str);
		ft_free(pars);
		str = readline("> ");
	}
}
