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
    IFS_TMP,
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
	R_INPUT,
	R_OUTPUT,
	R_DINPUT,
	R_DOUTPUT,
	REDIRECT_TMP
};

typedef struct s_node	t_node;

typedef struct s_node
{
	int					fd[2];
	char				*limiter;
	t_node				*next;
	t_node				*prev;
}						t_node;

typedef struct  s_start
{
    char        *str;
    char        **env;
    enum e_token *id;
}               t_start;

typedef struct s_pars
{
    int                 space;
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

//parsing

//parsing.c
int             ft_parsing(t_pars **pars, char **str, char **env);

//parsing_utils.c
int             is_redirect(enum e_pars token);
void            print_error(char *str);

//put_id.c
enum e_token    *put_id(char *str);
enum e_token    is_id(char c);

//expand.c
int            ft_expand(t_start *start);

//expand_utils.c
char            *del_quote(t_start *start, enum e_token quote);
void            check_id(t_start *start);
int             len_expand(char *str);

//free.c
int             ft_free_1(char *tmp, t_start *start);
int             ft_free_2(char *tmp, char *tmp2, t_start *start);
int             ft_free_3(t_pars *pars, t_pars *new, t_start *start);
void            ft_free_tab(char **tab);
void        	ft_free_lst(t_pars **pars);

//dollar.c
char            *get_value(t_start *start, char *str, int pos);

//create_pars.c
void            create_pars(t_start *start, t_pars **pars);

//create_pars_utils.c
t_pars          *ft_lstlast_(t_pars *lst);

//token.c
void            put_token(t_pars **pars);

//syntax.c
void            check_syntax(t_pars **pars, char **env);

//syntax_utils.c
void            check_error(t_pars *pars);
void            is_builtin(t_pars *pars);
int             check_next(t_pars *pars);

//signal.c
void            siginthandler(int signal);
void            siginthandler_fork(int signal);

//exec

void                    ft_free(t_pars **pars);
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
int						valid_arg(char *str);
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
void					ft_export(t_pars **pars, t_data *data);
void					ft_unset(t_pars **pars, t_data *data);
void					dup_cmdd(t_pars **pars, t_pipe *file);
void					init_pars(t_pars *pars);
void					set_doc(t_pipe *file, t_pars **pars);
void					ft_env_mult(t_data *data, t_pipe *file);
void					ft_pwd_mult(t_pipe *file);
void					free_nodess(t_pipe *file);
int						reading_in_one(t_pars **pars, t_pipe *file, int *last,
							t_pars **cmd);
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
