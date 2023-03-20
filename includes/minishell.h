/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:51:03 by tbelleng          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:55 by tbelleng         ###   ########.fr       */
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
# include "../libft/libft.h"


// mon gars Lucien dans cette structure je vais mettre les arguments generaux dont on a besoin
// pour les balader dans le programme sans soucis. hesite pas a faire des strucutres si ta besoin de truc pour rendre les
// choses plus claires.

// Dans les fonctions je prefere utiliser ft_putstr_fd aue un simple printf car apres on va surement travailler avec des pipes
// pour l'execution, et donc ca sera plus simple a rediriger dans les Fd.
// D'ailleurs dans le parsing il faut qu on pense a implenter une variable qui nous permet de savoir si ont doit rediriger dans la
// sortie standart ou dans des FD.


typedef struct s_args
{
    int     argc;
    char    **argv;
    char    **envp;
} t_args;


// *************************Built-in************************

int    ft_echo(t_args *data);
int     n_option(t_args *data);

//**********************************************************

#endif