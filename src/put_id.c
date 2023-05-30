#include "../includes/minishell.h"

enum e_token is_id(char c)
{
    if (c == '\"')
        return (D_QUOTE);
    else if (c == '\'')
        return (S_QUOTE);
    else if (c == '|')
        return (PIPE_C);
    else if (c == '<' || c == '>')
        return (REDIRECT);
    else if (c == '$')
        return (DOLLAR);
    else if (c == ' ' || c == '	' || c == '\n')
        return (IFS_TMP);
    else
        return (ALPHA_NUM);
}

enum e_token	*put_id(char *str)
{
    int	i;
    enum e_token    *id;

    i = -1;
    id = ft_calloc(sizeof(enum e_token), ft_strlen(str) + 1);
    if (!id)
    {
        free(id);
        exit (0);
    }
    while (str[++i])
        id[i] = is_id(str[i]);
    id[i] = FINISH;
    return (id);
}
