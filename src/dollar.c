#include "../includes/minishell.h"

extern int  g_global;

static char	*replace_dote(t_start *start, int i)
{
	char	*tmp;
	char	*nb;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(start->str) + 3);
	if (!tmp)
		exit(ft_free_1(tmp, start));
	while (j < i)
	{
		tmp[j] = start->str[j];
		j++;
	}
	i += 2;
	tmp[j] = 0;
	nb = ft_itoa(g_global);
	ft_strlcat(tmp, nb, ft_strlen(start->str) + 3);
	free(nb);
	if (start->str[i])
		ft_strlcat(tmp, start->str + i, ft_strlen(start->str));
	free(start->str);
	return (tmp);
}

static char    *ft_exist(int pos, t_start *start, char *env, char *tmp)
{
    int i;
    int size;
    char    *value;

    i = 0;
    size = (ft_strlen(start->str) - ft_strlen(tmp)) + (ft_strlen(env)
        - ft_strlen(tmp));
    value = ft_calloc(sizeof(char), size + 1);
    if (!value)
        exit(ft_free_2(tmp, value, start));
    while (i < pos)
    {
        value[i] = start->str[i];
        i++;
    }
    value[i] = 0;
    ft_strlcat(value, ft_strchr(env, '=') + 1, ft_strlen(env) + 1);
    i += ((int) ft_strlen(tmp));
    ft_strlcat(value, start->str + i, ft_strlen(start->str) + ft_strlen(env));
    free(start->str);
    free(tmp);
    return (value);
}

static char    *does_not_exist(char *tmp, t_start *start, int pos)
{
    char    *buff;
    int     i;
    int     j;

    i = 0;
    buff = ft_calloc(sizeof(char), (ft_strlen(start->str) - ft_strlen(tmp)) + 1);
    if (!buff)
        exit(ft_free_2(tmp, buff, start));
    while (i < pos)
    {
        buff[i] = start->str[i];
        i++;
    }
    j = i;
    i += (ft_strlen(tmp));
    while (start->str[i])
    {
        buff[j++] = start->str[i];
        i++;
    }
    buff[j] = 0;
    free(start->str);
    free(tmp);
    return (buff);
}

static char    *replace_value(char *tmp, t_start *start, int pos)
{
    int     i;

    i = 0;
    if (tmp[0] == '?')
    {
        free(tmp);
        return (replace_dote(start, pos));
    }
    while (start->env[i])
    {
        if (ft_strnstr(start->env[i], tmp, ft_strlen(tmp)) != NULL
            && start->env[i][ft_strlen(tmp) - 1] == '=')
            return (ft_exist(pos, start, start->env[i], tmp));
        else
            i++;
    }
    return (does_not_exist(tmp, start, pos));
}

char    *get_value(t_start *start, char *str, int pos)
{
    int i;
    int j;
    int u;
    char    *tmp;

    i = 0;
    u = -1;
    if (str[i] && str[i] == '$')
        i++;
    j = len_expand(str + i);
    if (j == 0)
        return (start->str);
    tmp = ft_calloc(sizeof(char), j + 2);
    if (!tmp)
        exit(ft_free_1(tmp, start));
    while (u < j)
        tmp[++u] = str[i++];
    tmp[u] = '=';
    tmp[u + 1] = 0;
    return (replace_value(tmp, start, pos));
}
