#include "../includes/minishell.h"

int g_global;

void    ft_free(t_pars **pars)
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

static void	cpy_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = ft_calloc(sizeof(char *), i + 1);
	if (!data->env)
	{
		free(data->env);
		exit(0);
	}
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env[i] = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_pars	*pars;
    t_data  data;

	(void)ac;
	(void)av;
	pars = NULL;
    ft_memset(&data, 0, sizeof(t_data));
    cpy_env(envp, &data);
    signal(SIGINT, &siginthandler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("> ");
	while (str)
	{
		add_history(str);
		if (ft_parsing(&pars, &str, data.env) != 2 && g_global == 0)
			trimm_exec(&pars, &data);
		ft_free(&pars);
		str = readline("> ");
	}
    ft_free_tab(data.env);
	free(str);
}
