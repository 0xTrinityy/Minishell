#include "../includes/minishell.h"

int	is_redirect(enum e_pars token)
{
	if (token == R_INPUT)
		return (1);
	else if (token == R_OUTPUT)
		return (1);
	else if (token == R_DINPUT)
		return (1);
	else if (token == R_DOUTPUT)
		return (1);
	else
		return (0);
}

void    print_error(char *str)
{
    ft_putstr_fd("minishell: syntax error near\n",1);
    ft_putstr_fd("unexcepted token ",1);
    ft_putstr_fd(str,1);
    ft_putstr_fd("\n",1);
}
