/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:40:52 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/30 16:44:07 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_id(t_start *start)
{
	int	i;

	i = 0;
	while (start->str[i])
	{
		if (start->id[i] == IFS)
			;
		else if (start->id[i] != is_id(start->str[i]))
			start->id[i] = is_id(start->str[i]);
		i++;
	}
	start->id[i] = FINISH;
}

char	*del_quote(t_start *start, enum e_token quote)
{
	char	*tmp;
	int		j;
	int		u;
	int		i;

	j = 0;
	u = 0;
	i = -1;
	tmp = ft_calloc(sizeof(char), ft_strlen(start->str) - 1);
	if (!tmp)
		exit(ft_free_1(tmp, start));
	while (start->str[j])
	{
		if (start->id[j] == quote && u < 2)
			u++;
		else
			tmp[++i] = start->str[j];
		if ((start->id[j] == IFS_TMP || start->str[j] == ' ') && u == 1)
			start->id[j - 1] = IFS;
		j++;
	}
	tmp[++i] = 0;
	free(start->str);
	return (tmp);
}

int	len_expand(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
		i++;
	return (i);
}
