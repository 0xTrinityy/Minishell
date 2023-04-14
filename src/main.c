/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:37:36 by luciefer          #+#    #+#             */
/*   Updated: 2023/04/09 15:40:52 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_comp(char *cmd)
{
	if(strcmp(cmd, "unset") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else
		return (0);
}

int	check_cmd(char *str)
{
	int	i;
	int	u;
	char	cmd[6];

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	u = i;
	while (str[i] && str[i] != ' ')
		i++;
	if ((i - u) > 6)
		return (0);
	i = 0;
	while(str[u] && str[u] != ' ')
	{
		cmd[i] = str[u];
		i++;
		u++;
	}
	if (!cmd_comp(cmd))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	while(1)
	{
		str = readline("$> ");
		if (!check_cmd(str))
			printf("error\n");
		exec_cmd(str);
		free(str);
	}
}
