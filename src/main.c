/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:01 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 18:40:11 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_global;

void	ft_free(t_pars **pars)
{
	t_pars	*next;
	int		i;

	i = 0;
	while (*pars != NULL)
	{
		next = (*pars)->next;
		free((*pars)->str);
		free((*pars)->id);
		free((*pars));
		*pars = next;
	}
	return ;
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	cpy_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
    data->env = ft_calloc(sizeof(char *), i + 1);
	if (!data->env)
    {
        free (data->env);
		exit (0);
    }
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env[i] = 0;
}

static void	printf_err(t_pars **pars)
{
    (void) pars;
	if (g_global == 2)
	{
		ft_putstr_fd("minishell: syntax error near\n", 1);
		ft_putstr_fd("unexpected token\n", 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
	t_data	data;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	pars = NULL;
	cpy_env(envp, &data);
	signal(SIGINT, &siginthandler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (str)
	{
		add_history(str);
		if (ft_parsing(&pars, str, data.env) != 2 && g_global == 0)
			trimm_exec(&pars, &data);
		else if (g_global != 0)
			printf_err(&pars);
		free(str);
		ft_free(&pars);
		str = readline("> ");
	}
	free(str);
	free_env(data.env);
}
