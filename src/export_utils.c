/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:09:51 by tbelleng          #+#    #+#             */
/*   Updated: 2023/05/26 12:11:37 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*var_trimmed(char *str)
{
	int		len;
	int		i;
	char	*tab;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
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

int	new_or_replace(t_data *data, char *str)
{
	int		i;
	char	*var;
	size_t	var_len;

	i = 0;
	var_len = to_equal(str);
	var = var_trimmed(str);
	while (data->env[i] != 0)
	{
		if (ft_strnstr(data->env[i], var, var_len) != NULL)
		{
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
	return (0);
}

char	*realloc_value(char *old, char *str, int size)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	str[i] = 0;
	free(old);
	return (new);
}

void	new_value(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*var;
	size_t	var_len;

	i = 0;
	j = 0;
	var_len = to_equal(str);
	var = var_trimmed(str);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var, var_len) != NULL)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(str);
			free(var);
			break ;
		}
		i++;
	}
}
