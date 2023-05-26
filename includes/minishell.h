/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:45:59 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/25 20:47:36 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h> 
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define ERR_INFILE "Infile error\n"
# define ERR_OUTFILE "Outfile error\n"
# define ERR_INPUT "Invalid number of arguments\n"
# define ERR_PIPE "Pipe error \n"
# define ERR_CMD "Command not found\n"
# define ERR_HEREDOC "Here_doc error\n"
# define ERR_UNLINK "Unlink error\n"
# define NO_PATH "Path not found\n"
# define INVALID_ID "not a valid identifier\n"
# define INFILE 0
# define HEREDOC 1

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
    BUILTIN,
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

typedef struct s_node t_node;

typedef struct  s_node
{
	int     fd[2];
	char    *limiter;
	t_node  *next;
	t_node  *prev;
}   t_node;

typedef struct	s_pars
{
	struct s_pars		*prev;
	int                 doc;
	char				*str;
	char                *limiter;
	enum e_token		*ID;
	enum e_pars			token;
	struct s_pars		*next;
}	t_pars;


typedef struct s_pipex
{
	pid_t	*pid;
	int		pidx;
	int		pid_numb;
	int		pipe_nb;
	int		cmd_nb;
	int     builtin;
	int     pipe_count;
	int		doc;
	int		*pipe;
	int		infile;
	char    *in_str;
	int     fd[2];
	int     prev_pipes;
	int     out_nb;
	int     *out_fd;
	int		outfile;
	char	*paths;
	char    *limit;
	char    **cmd_to_exec;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
    t_node  *node;
    t_node  *last;
}			t_pipe;


typedef struct s_data
{
	char    **env;
    char    *pwd;
}       t_data;


/********************* PARCING *********************/

void    check_cmd_valid(t_pars *pars);

// token.c

void		put_token(t_pars **pars, char **env);

// token2.c

void    give_cmd(t_pars *pars, int i);

// pars.c

t_pars	*ft_lstlast_(t_pars *lst);
void	_lst_back(t_pars *tmp, t_pars **pars);
t_pars  *get_word(t_pars **pars, char *str
		, enum e_token *ID, t_pars *new);
int ft_iter(char *str, enum e_token *ID);

// parcing.c

int	ft_parsing(t_pars **pars, char *str, char **env);
enum e_token	*char_ID(char *str);


/***************************************************/

int 	ft_free_all(t_pars **pars, enum e_token *id, int i);
int	    msg(char *err);
void	msg_error(char *err, t_pipe *data);
void	close_pipes(t_pipe *file);
void	parent_free(t_pipe *file);
void	pid_err(t_pipe *file);
void	infile_error(char *err, t_pipe *file);
void	error_free(t_pipe *file);

/*************************TRIM-CMD*************************/
void	dup_cmdd(t_pars **pars, t_pipe *file);
void	parent_free_one(t_pipe *file);
void	free_one_cmd_infile(t_pars **pars, t_pipe *file, t_data *data);
void	free_one_cmd_nofound(t_pars **pars, t_pipe *file, t_data *data);

void    only_file_handler(t_pars **pars);
int    only_file(t_pars **pars);
void    one_cmd(t_pipe *file, t_pars **pars, t_data *data);
int	    here_doc(t_pipe *file, t_pars **pars, t_data *data);
int     find_doc_fd(t_node *node, char *limiter);
void	init_pipes(t_pipe *file);
void    close_here_doc_pipe(t_node *node, int read, int write);
void    create_node_and_list(t_pipe *file, char *limiter);
t_pars* find_first_cmd(t_pars *pars);
t_pars  *find_previous_cmd(t_pars *pars);
void	set_doc(t_pipe *file, t_pars **pars);
void	init_pars(t_pars *pars);
/************************EXECUTION*************************/

//t_pars	*find_cmd_pars(t_pars *pars);
int    trimm_exec(t_pars **pars, t_data *data);
int	execution(t_pars **pars, char **envp);
//void	is_heredoc(t_pipe *file, t_pars **pars);
//void    infile_read(t_pipe *file, t_pars **pars);
void	out_read(t_pipe *file, t_pars **pars);
void	out_read_v2(t_pipe *file, t_pars **pars);

void	redirect_infirst(t_pars **pars, t_pipe *file, int *last, t_pars *cmd);
int	pass_pipe(t_pars **pars, t_pipe *file);
void	redirect_in2(t_pars **pars, t_pipe *file, int *last, t_pars *cmd);
int	redirect_in(t_pipe *file, t_pars **pars);

int	out_count(t_pars **pars, t_pipe *file, t_pars *tmp);
void	out_open(t_pars **pars, t_pipe *file);
int	redirect_out(t_pipe *file, t_pars **pars);

int	built_in_first(t_pars **pars, t_pars *tmp);
int	built_in_next(t_pars **pars, t_pipe *file, t_pars *tmp);
int	is_built_ins(t_pars **pars, t_pipe *file);

void	free_pars(t_pars **pars);
void	free_in(t_pars **pars, t_pipe *file, t_data *data);
void	free_builtin(t_pars **pars, t_pipe *file, t_data *data);
void	free_no_cmd(t_pars **pars, t_pipe *file, t_data *data);

void	neww(int infile, int outfile);
char	**return_arg(t_pars **pars, t_pipe *file, char **arg, int count);
char	**tema_larg2(t_pipe *file, t_pars **pars);

void    mult_cmd(t_pipe *file, t_pars **pars, t_data *data);
char	*find_path_spe(t_data *data);
//void    mult_cmd(t_pipe *file, t_pars **pars, char **envp);
//void	multiple_cmd(t_pipe file, char **envp);

void    redirect_hdoc(t_pars **pars, t_pipe *file);

/************************GNL******************************/

char		*get_next_line(int fd);
char		*ft_strjoin1(char *readed, char *buff);
int			ft_strlen1(char *str);
char		*getting_line(char *rest);
int			check(char *str);
char		*trimmed_buff(char *rest);
int			ft_strlen_classic(char *str);
int				cmd_comp(char *cmd);

char	*get_cmd(char **paths, char *cmd);
char	*find_path(char **envp);


/*************************BUILT-IN**************************/
void    builtin_exec(t_pars **pars, t_pipe *file, t_data *data);
void    builtin_exe_mult(t_pars **pars, t_pipe *file, t_data *data);
size_t	to_equal(char *str);
void    ft_echo(t_pars **pars, t_pipe *file);
void	ft_exit(t_pars *pars);
void    ft_env(t_data *data, t_pipe *file);
void    ft_pwd(void);
void    ft_cd(t_pars *pars, char **env);

char	*var_trimmed(char *str);
size_t	to_equal(char *str);
int	new_or_replace(t_data *data, char *str);
char	*realloc_value(char *old, char *str, int size);
void	new_value(t_data *data, char *str);

void    ft_export(t_pars **pars, t_data *data);
void    ft_unset(t_pars **pars, t_data *data);

// token2.c



// pars.c

void				create_pars(t_pars **pars, char *str, enum e_token *ID);

// parcing.c

void	put_id(char *str, enum e_token *ID);

// syntax.c

t_pars				*check_syntax(t_pars *pars, char **env);

// syntax_utils.c
void			del_quote(t_pars *pars);
void    replace_dollar(t_pars *pars, char **env, char *tmp);

// syntax_utils2.c
int				check_syntax_redirect(t_pars *pars, char **env);
int	is_redirect(enum e_pars pars);
void	ft_strcpy_dollar(char *tmp, char *str);
t_pars	*new_id(t_pars *pars);
char	*is_expand(t_pars *pars, char *tmp, int i);

// parsing_utils.c
t_pars	*ft_lstlast_(t_pars *lst);

// syntax_utils3.c
int	check_next(t_pars *pars);
int	check_binary(t_pars *pars);
void    is_builtin(t_pars *pars);
/***************************************************/

// signal.c
void	siginthandler(int signal);

void			ft_free(t_pars **pars);

// free.c
int	malloc_sec(t_pars *pars, t_pars *new);
int	malloc_sec2(t_pars *pars, char *tmp);
void	ft_free_tab(char **tab);
// exec.c
/*void	ft_exec(t_pars *pars, char *str);
void	ft_exit(t_pars *pars, char *str);
*/
#endif
