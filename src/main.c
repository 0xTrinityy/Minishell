/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 19:28:59 by tbelleng         ###   ########.fr       */
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

void    malloc_word(char **env, t_data *data)
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
    data->env[i] = 0;
}

void   cpy_env(char **envp, t_data *data)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    data->env = malloc(sizeof(char *) * (i + 1));
    if(!data->env)
        return ;
    i = 0;
    //malloc_word(envp, data);
    while(envp[i] != NULL)
    {
        data->env[i] = ft_strdup(envp[i]);
        i++;
    }
    data->env[i] = NULL;
}


int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
    int     i;
    t_data   data;

	(void) ac;
	(void) av;
	ft_memset(&data, 0, sizeof(t_data));
	pars = NULL;
    cpy_env(envp, &data);
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
