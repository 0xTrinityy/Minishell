/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:45:59 by luciefer          #+#    #+#             */
/*   Updated: 2023/05/29 10:46:11 by tbelleng         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
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
# define NO_PATH "Path not found\n No such file or directory\n"
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
void					builtin_exec(t_pars **pars, t_data *data, t_pipe *file);
void					builtin_exe_mult(t_pars **pars, t_pipe *file,
							t_data *data);
size_t					to_equal(char *str);
void					ft_echo(t_pars **pars, t_pipe *file);

void					ft_exit_built(t_pars **pars, t_pipe *file,
							t_data *data);
void					error_message_exit(char *str);
long long				ft_atoull(const char *str);
int						ft_isdigit_special(int arg);
void					ft_exit_built_mult(t_pars **pars, t_pipe *file,
							t_data *data);
void					ft_exit(t_pars *pars);
void					ft_env(t_data *data, t_pipe *file);
void					ft_pwd(t_pipe *file);
void					ft_cd(t_pars *pars, char **env);
int						valid_arg(char *str);
void					ft_export(t_pars **pars, t_data *data);
void					ft_unset(t_pars **pars, t_data *data);
void					create_pars(t_pars **pars, char *str, enum e_token *ID,
							char **env);
int						len_redirect(enum e_token *ID, char *str);
void					put_id(char *str, enum e_token *ID);
t_pars					*check_syntax(t_pars *pars, char **env);
void					del_quote(t_pars *pars);
void					replace_dollar(t_pars *pars, char **env, char *tmp);
int						check_syntax_redirect(t_pars *pars, char **env);
int						is_redirect(enum e_pars pars);
int						ft_strcpy_dollar(char *tmp, char *str);
t_pars					*new_id(t_pars *pars, char **env);
char					*is_expand(t_pars *pars, char *tmp, int i);
t_pars					*ft_lstlast_(t_pars *lst);
void					ft_exist(char *tmp, t_pars *pars, char *env, char *exp);
int						find_env(t_pars **pars, char *tmp, char **env,
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
int						malloc_sec4(t_pars *pars, char *str, char **env,
							char *str2);
void					dup_cmdd(t_pars **pars, t_pipe *file);
void					init_pars(t_pars *pars);
void					set_doc(t_pipe *file, t_pars **pars);
void					ft_env_mult(t_data *data, t_pipe *file);
void					ft_pwd_mult(t_pipe *file);

int						reading_in_one(t_pars **pars, t_pipe *file, int *last,
							t_pars *cmd);
int						one_cmd_in(t_pipe *file, t_pars **pars);
int						reading_out(t_pars **pars, t_pipe *file, int last);
int						one_cmd_out(t_pipe *file, t_pars **pars);
int						arg_count(t_pars **pars);
char					**tema_larg(t_pars **pars, t_pipe *file);
void					getting_args(t_pars **pars, t_pipe *file);

int						is_regular_file(const char *path);
void					free_isfile(t_pars **pars, t_pipe *file, t_data *data);
void					dup_cmdd(t_pars **pars, t_pipe *file);
void					parent_free_one(t_pipe *file);
void					free_one_cmd_infile(t_pars **pars, t_pipe *file,
							t_data *data);
void					free_one_cmd_isfile(t_pars **pars, t_pipe *file,
							t_data *data);
void					free_one_cmd_nofound(t_pars **pars, t_pipe *file,
							t_data *data);
void					init_pipes(t_pipe *file);
void					set_doc(t_pipe *file, t_pars **pars);
void					init_pars(t_pars *pars);

void					creating_append(t_pars **pars, t_pipe *file, int *last);
void					redirect_infirst(t_pars **pars, t_pipe *file, int *last,
							t_pars *cmd);
int						pass_pipe(t_pars **pars, t_pipe *file);
void					redirect_in2(t_pars **pars, t_pipe *file, int *last,
							t_pars *cmd);
int						redirect_in(t_pipe *file, t_pars **pars);

int						out_count(t_pars **pars, t_pipe *file, t_pars *tmp);
void					out_open(t_pars **pars, t_pipe *file);
void					redirect_output(t_pipe *file, int *last, int nb_rd,
							t_pars *cmd);
int						redirect_out(t_pipe *file, t_pars **pars);

int						built_in_first(t_pars **pars, t_pars *tmp);
int						built_in_next(t_pars **pars, t_pipe *file, t_pars *tmp);
void					mult_builtexx(t_pars **pars, t_pipe *file,
							t_data *data);
int						is_built_ins(t_pars **pars, t_pipe *file);

void					free_pars(t_pars **pars);
void					free_in(t_pars **pars, t_pipe *file, t_data *data);
void					free_builtin(t_pars **pars, t_pipe *file, t_data *data);
void					free_no_cmd(t_pars **pars, t_pipe *file, t_data *data);

void					neww(int infile, int outfile);
char					**return_arg(t_pars **pars, t_pipe *file, char **arg,
							int count);
char					**tema_larg2(t_pipe *file, t_pars **pars);

char					*var_trimmed(char *str);
int						new_or_replace(t_data *data, char *str);
char					*realloc_value(char *old, char *str, int size);
void					new_value(t_data *data, char *str);
void					only_expand(t_pars **pars, char **env, char *exp);

#endif
