/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/15 15:29:41 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_global;

void	ft_free(t_pars **pars)
{
    t_pars  *next;
    int     i;

    i = 0;
	while (*pars != NULL)
	{
        next = (*pars)->next;
	    free((*pars)->str);
		free((*pars)->ID);
        free((*pars));
		*pars = next;
	}
	return ;
}

void    free_env(char **env)
{
    int     i;

    i = 0;
    while(env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

void    cpy_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return ;
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
    data->env[i] = 0;
	//return (data->env);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
    t_data	data;
    t_pars  *tmp;

	(void)ac;
	(void)av;
    printf("%s\n", envp[0]);
	ft_memset(&data, 0, sizeof(t_data));
	pars = NULL;
	cpy_env(envp, &data);
	signal(SIGINT, &siginthandler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (str)
	{
		add_history(str);
		ft_parsing(&pars, str, data.env);
    tmp = pars;
		if (g_global == 0)
			trimm_exec(&pars, &data);
    pars = tmp;
		free(str);
		ft_free(&pars);
		str = readline("> ");
	}
    free_env(data.env);
}
