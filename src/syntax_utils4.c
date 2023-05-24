#include "../includes/minishell.h"

extern int  g_global;

void    check_error(t_pars *pars)
{
    if (pars->str[0] == '&' || pars->str[0] == ';'
        || pars->str[0] == '(' || pars->str[0] == ')')
        g_global = 2;
}
