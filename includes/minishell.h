/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:45:59 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/01 11:52:12 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"

enum	e_token
{
	ALPHA_NUM,
	IFS,
	S_QUOTE,
	D_QUOTE,
	DOLLAR,
	PIPE_C,
	REDIRECT,
	FINISH
};

enum	e_pars
{
	N_SORTED,
	CMD,
	PIPE,
	ARG,
	EXPAND,
	R_INPUT,
	R_OUTPUT,
	R_DINPUT,
	R_DOUTPUT,
	REDIRECT_TMP,
	TXT,
	TXT_S,
	TXT_D
};

typedef struct	s_pars
{
	struct s_pars		*prev;
	char				*str;
	enum e_token		*ID;
	enum e_pars			token;
	struct s_pars		*next;
}	t_pars;

/********************* PARCING *********************/

// token.c

void			put_token(t_pars **pars);

// token2.c

enum e_pars		check_quoted(char *str, enum e_token *ID);

// pars.c

int				create_pars(t_pars **pars, char *str, enum e_token *ID);

// parcing.c

int				ft_parcing(t_pars **pars, char *str, char **env);
void	put_id(char *str, enum e_token *ID);

// syntax.c

int				check_syntax(t_pars **pars, char **env);

// syntax_utils.c
void			del_quote(t_pars *pars);
void			replace_dollar(t_pars *pars, char **env);

// syntax_utils2.c
int				check_syntax_redirect(t_pars *pars);
int	is_redirect(enum e_pars pars);

// parsing_utils.c
t_pars	*ft_lstlast_(t_pars *lst);
/***************************************************/

// signal.c
void	siginthandler(int signal);

void			ft_free_all(void);

#endif
