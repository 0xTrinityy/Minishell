/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:51:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/14 13:51:04 by luciefer         ###   ########.fr       */
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
# include "../libft/libft.h"

# define ERR_INFILE "Infile error\n"
# define ERR_OUTFILE "Outfile error\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe error \n"
# define ERR_CMD "Command not found\n"
# define ERR_HEREDOC "Here_doc error\n"
# define ERR_UNLINK "Unlink error\n"
# define NO_PATH "Path not found\n"
// mon gars Lucien dans cette structure je vais mettre les arguments generaux dont on a besoin
// pour les balader dans le programme sans soucis. hesite pas a faire des strucutres si ta besoin de truc pour rendre les
// choses plus claires.

// Dans les fonctions je prefere utiliser ft_putstr_fd aue un simple printf car apres on va surement travailler avec des pipes
// pour l'execution, et donc ca sera plus simple a rediriger dans les Fd.
// D'ailleurs dans le parsing il faut qu on pense a implenter une variable qui nous permet de savoir si ont doit rediriger dans la
// sortie standart ou dans des FD.

// fait une fonctions type "struct init" qui malloc argv et envp et qui leur donne leur arguments

//THOMAS TO DO :
    //- Dans le built in CD, ne pas oublier de faire une fonction qui reload le pwd a chaque utilisation et qui donc change l'envp.
            //du coup il faut free puis re-malloc envp avec le nouveau OLDPWD.

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

enum	e_parc
{
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

struct	s_list
{
	t_list		*prev;
	char		*str;
	enum e_parc	token;
	t_list		*next;
}	t_list;


// *************************Built-in************************

int    ft_echo(char **str);
int    n_option(char *str);

/*char	*find_path(char **envp);
void    ft_pwd(char **envp);

void    ft_env(t_args *data);

void	ft_export(t_args *data, char *str);

// gestion d'erreur Built-in
int	msg(char *err);*/

//**********************************************************

void	exec_cmd(char *str);

#endif
