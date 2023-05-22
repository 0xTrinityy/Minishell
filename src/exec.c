/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:18:26 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/17 18:35:00 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

void	ft_exec(t_pars *pars, char *str, char **env)
{
	if (is_a_cmd(pars->str, env) == 2)
		ft_exit(pars, str);
}

int	nb_fd(t_pars *pars)
{
	t_pars	*tmp;
	int		i;

	i = 0;
	tmp = pars;
	while (pars != NULL)
	{
		if (pars->token == PIPE)
			i += 2;
		if (is_redirect(pars->token))
			i++;
		pars = pars->next;
	}
	return (i);
}

void	ft_exit(t_pars *pars, char *str)
{
	int	i;

	i = 0;
	while (i < nb_fd(pars))
		close(i++);
	ft_free(pars);
	free(str);
	g_global = 2;
	exit (0);
}

static char    *get_home(char **env)
{
    (void) env;
    return("/mnt/nfs/homes/luciefer")
}

static int    change_dir(char *str)
{
    char *tmp;

    tmp = getcwd(NULL, 0);
    if (tmp == NULL)
    {
        printf("erreur no path");
        return (0);
    }
    i = chdir(str);
    if (i == -1)
    {
        g_global = 1;
        ft_putstr_fd("cd: ",1);
        ft_putstr_fd(pars->str, 1);
        ft_putstr_fd(": No such file or directory\n", 1);
        return (0);
    }
    free(tmp);
    return (1);
}

void    ft_cd(t_pars *pars, char **env)
{
    int i;
    char    *path;

    if (!pars->next || is_redirect(pars->next->token))
        path = get_home(env);
    else
    {
        pars = pars->next;
        path = pars->str;
    }
    if (pars->next != NULL && pars->next->token == ARG)
    {
        printf("cd: too many arguments\n");
        g_global = 1;
        return ;
    }
    if (pars->str[0] == '-' && pars->str[1] == '-')
    {
        printf("cd: --: invalid option\n");
        g_global = 2;
        return ;
    }
    if(!change_dir(path))
        return ;
    g_global = 0;
}
