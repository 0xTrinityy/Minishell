/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:15 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/11 19:06:00 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*var_trimmed(char *str)
{
	size_t	len;
	int		i;
	char	*tab;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tab = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

size_t	to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (i);
}

char    **ft_unset(t_args *data, char *str)
{
	int     i;
	int     k;
	char    *var;
	char    **new;
	size_t  var_len;
	
	
	i = 0;
	k = 0;
	while (data->envp[i])
		i++;
	new = malloc(sizeof(char *) * (i - 1));
	if (!new)
		return (NULL);
	var = var_trimmed(str);
	var_len = to_equal(str);
	while(data->envp[i])
	{
		if (strncmp(data->envp[i], str, var_len) == NULL)
			i++;
		else
		{
			new[k] = ft_strdup(data->envp[i]);
			k++;
			i++;
		}
	}
	new[k] = 0;
	return (new);
}