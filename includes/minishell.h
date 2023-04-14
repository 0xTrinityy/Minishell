/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:51:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/14 14:08:01 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# define INVALID_ID "not a valid identifier\n"
// mon gars Lucien dans cette structure je vais mettre les arguments generaux dont on a besoin
// pour les balader dans le programme sans soucis. hesite pas a faire des strucutres si ta besoin de truc pour rendre les
// choses plus claires.

// Dans les fonctions je prefere utiliser ft_putstr_fd aue un simple printf car apres on va surement travailler avec des pipes
// pour l'execution, et donc ca sera plus simple a rediriger dans les Fd.
// D'ailleurs dans le parsing il faut qu on pense a implenter une variable qui nous permet de savoir si ont doit rediriger dans la
// sortie standart ou dans des FD.

// fait une fonctions type "struct init" qui malloc argv et envp et qui leur donne leur arguments

//THOMAS TO DO :
//- Dans le built in CD,
//ne pas oublier de faire une fonction qui reload le pwd a chaque utilisation et qui donc change l'envp.
//du coup il faut free puis re-malloc envp avec le nouveau OLDPWD.

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;

}			t_args;

// *************************Built-in************************

int			ft_echo(t_args *data);
int			n_option(t_args *data);

char		*find_path(char **envp);
void		ft_pwd(char **envp);

void		ft_env(t_args *data);
int    ft_ecXho(char **str);
int    n_option(char *str);

/*char	*find_path(char **envp);
void    ft_pwd(char **envp);

char		**ft_export(t_args *data, char *str);

char		**ft_unset(t_args *data, char *str);

void		ft_exit(unsigned long long int nb);

size_t		to_equal(char *str);
char		*var_trimmed(char *str);

int			ft_cd(t_args *data, char *str);

//gestion d'erreur Built-in
void		msg_error(char *err, char *str);

// gestion d'erreur Built-in
int	msg(char *err);*/

//**********************************************************

void	exec_cmd(char *str);

#endif
