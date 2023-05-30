#include "../includes/minishell.h"

extern int  g_global;

void	ft_free_lst(t_pars **pars)
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

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int ft_free_3(t_pars *pars, t_pars *new, t_start *start)
{
    ft_free_lst(&pars);
    ft_free_lst(&new);
    free(start->str);
    free(start->id);
    return (0);
}

int ft_free_1(char *tmp, t_start *start)
{
    free(tmp);
    free(start->str);
    free(start->id);
    return (0);
}

int ft_free_2(char *tmp, char *tmp2, t_start *start)
{
    free(tmp2);
    return (ft_free_1(tmp, start));
}
