/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:37:04 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 18:37:06 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_global;

static char	*get_home(char **env)
{
	(void)env;
	return ("/mnt/nfs/homes/luciefer");
}

static int	change_dir(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		printf("error no path");
		return (0);
	}
	i = chdir(str);
	if (i == -1)
	{
		g_global = 1;
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

void	change_env_pwd(char **env, char *str)
{
	char	new_pwd[4096];
	int		j;
	int		i;

	j = 0;
	i = 0;
	getcwd(new_pwd, 4096);
	while (env[j])
	{
		if (ft_strnstr(env[j], str, 4) != NULL)
			break ;
		j++;
	}
	while (env[j][i] != '=')
		i++;
	i = i + ft_strlen(new_pwd) + 1;
	free(env[j]);
	env[j] = malloc(sizeof(char) * (i + 1));
	if (!env[j])
        exit(0);
	env[j][0] = 0;
	i = ft_strlen(str);
	ft_strlcat(env[j], str, i + 1);
	ft_strlcat(env[j] + i, new_pwd, ft_strlen(new_pwd) + 1);
}

void	change_env_oldpwd(char **env, char *old_pwd, char *str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (env[j])
	{
		if (ft_strnstr(env[j], str, ft_strlen(str)) != NULL)
			break ;
		j++;
	}
	while (env[j][i] != '=')
		i++;
	i = i + ft_strlen(old_pwd) + 1;
	free(env[j]);
	env[j] = malloc(sizeof(char) * (i + 1));
	if (!env[j])
		exit (0);
	env[j][0] = 0;
	i = ft_strlen(str);
	ft_strlcat(env[j], str, i + 1);
	ft_strlcat(env[j] + i, old_pwd, ft_strlen(old_pwd) + 1);
}

void	ft_cd(t_pars *pars, char **env)
{
	char	*path;
	char	old_pwd[4096];

	if (!pars->next || is_redirect(pars->next->token))
		path = get_home(env);
	else
	{
		pars = pars->next;
		path = pars->str;
	}
	if (pars->next != NULL && pars->next->token == ARG)
		return ((void)msg("cd: too many arguments\n", 1));
	if (pars->str[0] == '-' && pars->str[1] == '-')
		return ((void)msg("cd: --: invalid option\n", 2));
	getcwd(old_pwd, 4096);
	if (!change_dir(path))
		return ;
	change_env_pwd(env, "PWD=");
	change_env_oldpwd(env, old_pwd, "OLDPWD=");
	g_global = 0;
}
