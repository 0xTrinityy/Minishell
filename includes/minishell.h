/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciefer <luciefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:45:59 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/24 18:36:25 by luciefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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

# include "../libft/libft.h"
# include <signal.h>

enum					e_token
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

enum					e_pars
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

typedef struct s_node	t_node;

typedef struct s_node
{
	int					fd[2];
	char				*limiter;
	t_node				*next;
	t_node				*prev;
}						t_node;

typedef struct s_pars
{
	struct s_pars		*prev;
	int					doc;
	char				*str;
	char				*limiter;
	enum e_token		*id;
	enum e_pars			token;
	struct s_pars		*next;
}						t_pars;

typedef struct s_pipex
{
	pid_t				*pid;
	int					pidx;
	int					pid_numb;
	int					pipe_nb;
	int					cmd_nb;
	int					builtin;
	int					pipe_count;
	int					doc;
	int					*pipe;
	int					infile;
	char				*in_str;
	int					fd[2];
	int					prev_pipes;
	int					out_nb;
	int					*out_fd;
	int					outfile;
	char				*paths;
	char				*limit;
	char				**cmd_to_exec;
	char				**cmd_paths;
	char				**cmd_args;
	char				*cmd;
	t_node				*node;
	t_node				*last;
}						t_pipe;

typedef struct s_data
{
	char				**env;
	char				*pwd;
}						t_data;

void					check_cmd_valid(t_pars *pars);
void					put_token(t_pars **pars, char **env);
void					give_cmd(t_pars *pars, int i);
t_pars					*ft_lstlast_(t_pars *lst);
void					_lst_back(t_pars *tmp, t_pars **pars);
t_pars					*get_word(t_pars **pars, char *str, enum e_token *ID,
							t_pars *new);
int						ft_iter(char *str, enum e_token *ID);
int						ft_parsing(t_pars **pars, char *str, char **env);
enum e_token			*char_ID(char *str);
void					is_cmd(t_pars **pars, t_pipe *file, char **envp);
void					check_error(t_pars *pars);
void					check_pipe(t_pars *pars);
int						ft_free_all(t_pars **pars, enum e_token *id, int i);
int						msg(char *err, int i);
void					msg_error(char *err, t_pipe *data);
void					close_pipes(t_pipe *file);
void					parent_free(t_pipe *file);
void					pid_err(t_pipe *file);
void					infile_error(char *err, t_pipe *file);
void					error_free(t_pipe *file);
void					close_all1(t_pipe *file);
void					parent_free1(t_pipe *file);
void					child_free1(t_pipe *file);
void					only_file_handler(t_pars **pars);
int						only_file(t_pars **pars);
void					one_cmd(t_pipe *file, t_pars **pars, t_data *data);
int						here_doc(t_pipe *file, t_pars **pars, t_data *data);
int						find_doc_fd(t_node *node, char *limiter);
void					close_here_doc_pipe(t_node *node, int read, int write);
void					create_node_and_list(t_pipe *file, char *limiter);
t_pars					*find_first_cmd(t_pars *pars);
t_pars					*find_previous_cmd(t_pars *pars);
int						trimm_exec(t_pars **pars, t_data *data);
int						execution(t_pars **pars, char **envp);
void					out_read(t_pipe *file, t_pars **pars);
void					out_read_v2(t_pipe *file, t_pars **pars);
void					mult_cmd(t_pipe *file, t_pars **pars, t_data *data);
char					*find_path_spe(t_data *data);
void					redirect_hdoc(t_pars **pars, t_pipe *file);
char					*get_next_line(int fd);
char					*ft_strjoin1(char *readed, char *buff);
int						ft_strlen1(char *str);
char					*getting_line(char *rest);
int						check(char *str);
char					*trimmed_buff(char *rest);
int						ft_strlen_classic(char *str);
int						cmd_comp(char *cmd);
char					*get_cmd(char **paths, char *cmd);
char					*find_path(char **envp);
void					builtin_exec(t_pars **pars, t_pipe *file, t_data *data);
void					builtin_exe_mult(t_pars **pars, t_pipe *file,
							t_data *data);
size_t					to_equal(char *str);
void					ft_echo(t_pars **pars, t_pipe *file);
void					ft_exit(t_pars *pars);
void					ft_env(t_data *data, t_pipe *file);
void					ft_pwd(void);
void					ft_cd(t_pars *pars, char **env);
void					ft_export(t_pars **pars, t_data *data);
void					ft_unset(t_pars **pars, t_data *data);
void					create_pars(t_pars **pars, char *str, enum e_token *ID);
int						len_redirect(enum e_token *ID, char *str);
void					put_id(char *str, enum e_token *ID);
t_pars					*check_syntax(t_pars *pars, char **env);
void					del_quote(t_pars *pars);
void					replace_dollar(t_pars *pars, char **env, char *tmp);
int						check_syntax_redirect(t_pars *pars, char **env);
int						is_redirect(enum e_pars pars);
void					ft_strcpy_dollar(char *tmp, char *str);
t_pars					*new_id(t_pars *pars);
char					*is_expand(t_pars *pars, char *tmp, int i);
t_pars					*ft_lstlast_(t_pars *lst);
void					ft_exist(char *tmp, t_pars *pars, char *env, char *exp);
void					find_env(t_pars **pars, char *tmp, char **env,
							char *exp);
int						check_next(t_pars *pars);
int						check_binary(t_pars *pars);
void					is_builtin(t_pars *pars);
void					siginthandler(int signal);
void					siginthandler_fork(int signal);
void					ft_free(t_pars **pars);
int						malloc_sec(t_pars *pars, t_pars *new);
int						malloc_sec2(t_pars *pars, char *tmp);
void					ft_free_tab(char **tab);
int						malloc_sec3(t_pars *pars, char *str, char **env);

#endif
