/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/14 17:37:36 by tbelleng         ###   ########.fr       */
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

void    malloc_word(char **env, t_pipe *data)
{
    int i;
    int j;

    i = 0;
    while (env[i])
    {
        j = 0;
        while(env[i][j])
            j++;
        data->env[i] = malloc(sizeof(char) * j + 1);
        if (!data->env[i])
            return ;
        i++;
    }
    data->env[i - 1] = 0;
}

 char **cpy_env(char **envp, t_pipe *data)
{
    int i;

    i = 0;
    while(envp[i])
        i++;
    data->env = malloc(sizeof(char *) * i + 1);
    if(!data->env)
        return (0);
    i = 0;
    malloc_word(envp, data);
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
	ft_memset(&data, 0, sizeof(t_pipe));
	pars = NULL;
    data.env = cpy_env(envp, &data);
	signal (SIGINT, &siginthandler);
	signal (SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (str)
	{
		add_history(str);
        i = ft_parsing(&pars, str, data.env);
        if (i == 1)
			trimm_exec(&pars, &data);
		free(str);
		ft_free(pars);
		str = readline("> ");
	}
}
