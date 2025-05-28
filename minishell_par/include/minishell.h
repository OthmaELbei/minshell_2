/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbied <oelbied@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:22:56 by sidrissi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 21:51:43 by sidrissi         ###   ########.fr       */
=======
/*   Updated: 2025/05/28 11:40:13 by oelbied          ###   ########.fr       */
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca
/*                                                                            */
/* ************************************************************************** */

// MAZAL ERROR F HERDOC TEST:  << "$VAR" || $"$var"$HOME

#ifndef MINISHELL_H
<<<<<<< HEAD
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#include <termios.h>

#define ERROR "syntax error near unexpected token\n"
#define name_length 9
=======
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <sys/stat.h>
# include <termios.h>

# define ERROR "syntax error near unexpected token\n"
# define name_length 9
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca

typedef enum s_keyword
{
	WRITE_OUT,
	READ_IN,
	APPEND,
	HERDOC,
	PIPE,
	PIPES,
	WORD,
	START,
	FREAD_IN,
	FWRITE_OUT,
	F_HERDOC,
	F_APPEND,
	CMD,
	ambigous,
	no_ambigous,
}	t_keyword;
typedef struct t_list
{
	char			*data;
	struct t_list	*next;
}	t_list;

typedef struct t_listenv
{
	char				*constvrble;
	char				*pat;
	// int					fdd;
	  int valid;
	struct t_listenv	*next;
}	t_listenv;

typedef struct s_expcall
{
	int		x;
	char	*splt_egal;
	char	**splt_plus;
	char	*segal;
}	t_expcall;

typedef struct s_exptow
{
	char	*juny;
	char	*pats;
	int		found_flag;
}	t_exptow;

typedef struct s_unset
{
	int		flags;
	char	*data;
}	t_unset;

typedef struct s_quote_data
{
	char	*line;
	int		*i;
	char	**buffer;
}	t_quote_data;

typedef struct s_initalize
{
	int		j;
	char	quote;
	char	*new_buffer;
	char	*res;
}	t_initalize;

typedef struct s_token
{
	char			**value;
	int				fd;
	t_keyword		type;
	t_keyword		_ambigous;
	int				error;
	int				herdoc;
<<<<<<< HEAD
	struct s_token 	*next;
} t_token;
=======
	struct s_token	*next;
}	t_token;
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca

typedef struct s_expand
{
	char	*res;
	int		i;
	int		dollar_count;
	int		var_len;
	char	*var_name;
	int		flag;
}	t_expand;

typedef struct s_tg
{
	t_keyword	type;
	int			quote;
}	t_tg;

typedef struct s_v_main
{
	char	*line;
	int		flag;
}	t_v_main;

typedef struct s_redir
{
	char			*name;
	int				fd;
	t_keyword		type;
	t_keyword		_ambigous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_data
{
	char			*cmd;
	char			**args;
	t_redir			*file;
	struct s_data	*next;
}	t_data;

typedef struct s_var_data
{
<<<<<<< HEAD
	t_data *current;
	t_data *next;
	t_redir *redir;
	t_redir *next_redir;
	int i;
} t_var_data;

// typedef struct s_exit_status
// {
// 	int	exit_status;
// }	t_exit_status;

/*********************Parsing**********************/

/*main.c*/
int check_quotes(char *line, int i, int count_quote);
t_token *lexing(char *line, int *flag, t_listenv *head);
int	helper_main(t_token *tokens, int *flag, t_listenv *head);
// void lexing(char *line);

/*---------------tokenization---------------*/
int sp(char c);
t_token *tokenization(char *line, int i);
void handle_quotes(t_quote_data *data, t_initalize *init);
/*---------------garbage---------------*/
// Linked list:
void free_tokens(t_token *tokens);
t_token *deldum(t_token **head);
void free_data(t_data *data);

/*---------------error---------------*/
int error(t_token *tokens, t_token *current);
int is_redirect(t_keyword type);
int is_pipe(t_keyword type);
int pipe_check(t_token *prev, t_token *next);

/*---------------expand---------------*/
void ft_expand(t_token *tokens, int i, t_listenv *head);
void handle_single_quote(t_expand *ex, t_token *tokens);
void process_dollar(t_expand *ex, t_token *tokens, t_listenv *head, t_tg *data);
void handle_odd_dollars(t_expand *ex, t_token *tokens, t_listenv *head, t_tg *data);
void extract_var(t_expand *ex, char *str);
void append_char(t_expand *ex, char c);
void handle_num(t_expand *ex, t_token *tokens);
void handle_status(t_expand *ex, int status);
/*---------------ft_rename------------*/
void ft_rename(t_token *tokens);

/*-------------ft_herdoc--------------*/
int	ft_herdoc(t_token **tokens, t_listenv *head);
char **ft_expand_herdoc(char *str, int *flag, t_listenv *head);
void handle_odd_dollars_herdoc(t_expand *ex, char *str,
							   int *flag, t_listenv *head);
void extract_var_herdoc(t_expand *ex, char *str);
void append_char_herdoc(t_expand *ex, char c);
int check_delimter(char *delimter);
char *generate_name(void);
char *get_word(int fd);

/*-------------parsing--------------*/
t_data *parsing(t_token **tokens, t_token *temp);
t_data *ft_lstnew_p(void);

/*===============libft===============*/
char *ft_substr(char *s, int start, int len);
void ft_putstr_fd(char *s, int fd);
int ft_strlen(char *s);
char *ft_strdup(char *s);
int ft_isprint(int c);
int ft_cmp(char *word);
char *ft_strjoin(char *s1, char *s2);
// Linked list:
t_token *ft_lstlast(t_token *lst);
t_token *ft_lstnew(char *content, t_keyword type);
void ft_lstadd_back(t_token **lst, t_token *new);

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
void *ft_memset(void *b, int c, size_t len);
int ft_strcmp(char *s1, char *s2);
char *ft_itoa(int n);

/***************ft_split************* */
void *ft_free(char **strs, int count);
char **ft_split(char *s, char c);
int word_count(char *s, char c);

/***************fake_herdoc************* */
int	ft_open_herdoc_until_error(t_token *current, t_listenv *head);

void ft_ambigous(char *env_name, t_expand *ex, t_tg *data, t_token *tokens);

/******************************************************/

void ft_lstadd_back_ex(t_listenv **lst, t_listenv *new);
t_listenv *ft_lstnew_env(char *content, char *path);
void ft_lstdelone(t_listenv *lst, void (*del)(void *));
int ft_lstsize(t_listenv *lst);
int ft_env(char **env, t_listenv **head);
int ft_tchc_data(t_data *data, t_listenv **head);
int ft_pwd(t_listenv *head);
int ft_echo(t_data *data);
int ft_unset(t_data *data, t_listenv **head);
int ft_exit(t_data *data);
int ft_cd(t_data *data, t_listenv *head);
int ft_export(t_listenv *head, t_data *data);
int thcking_pluss(char *str);
int tchking_egal(char *str);
char *ft_strchr(const char *s, int c);
char *ft_tchk_cotachen(char *s1);
char **ft_ar_env(t_listenv *head);
size_t ft_strlcpy(char *dst, char *src, size_t dstsize);
int ft_execoshen(t_data *data, t_listenv *head);
int	ft_strncmp(char *s1, char *s2, int n);
char *get_command_path(char *commnd, char **ary_envp, int *);
char *ft_strcpy(char *dst, const char *src);
int ft_isalpha(int c);
void ft_lstclear(t_listenv **lst, void (*del)(void *));

// export
int is_builtin(t_data *data, t_listenv **head);
t_listenv *tcchk_untel_egall(char *data, t_listenv *head);
int tcchk_untel_egll(char *data, t_listenv *head);
int ft_tchck_argmo_exat(char *data);
// void tchek_only_key(char *data,char *splt_egal , char **splt_plus,t_listenv **head);
void tchek_only_key(char *data, t_expcall *call, t_listenv **head);
void free_copy_listenv(t_listenv *head);
// void separe_egal_pluss(t_data *data, int x,char *splt_egal,char **splt_plus,char  *segal ,t_listenv **head);
void separe_egal_pluss(t_data *data, t_expcall *call, t_listenv **head);

void extract_name_and_value(char *arg, char **name, char **value);
// void ft_egal_pacslash(t_data *data, char *splt_egal, char **splt_plus, t_listenv *joune, t_listenv *head);

t_listenv *find_variable(t_listenv *head, char *name);
int find_varble(t_listenv *head, char *name);
int ft_lstsize_data(t_data *lst);
void *ft_free(char **strs, int count);
int tf_tchee_redercter(t_data *data, t_listenv **head);
void ft_closse(t_redir *redir, int fd);
void ft_free_ex(char **str);
void function_call(t_listenv **head, t_data *data);
void only_key(char *data, char **splt_plus, t_listenv **head);
void cleanup_memory(char *splt_egal, char **splt_plus, char *segal);
void my_del(void *ptr);
char *ft_strdup_unset(char *s);
int ft_tchk_value(char *data);
t_listenv *copy_listenv(t_listenv *head);
void pluss_egal(t_data *data, int x, t_listenv *head, char *segal);
void extract_name_and_value(char *arg, char **name, char **value);
int ft_strlen_name(int *i, char *arg);
void ft_egal_pacslash(t_data *data, char *splt_egal, char **splt_plus, t_listenv *head);
void pluss_egal_pacslash(t_data *data, int x, t_listenv **head, char *segal);
char *store_pwd(char *str, int flag);
void ft_freee(char **arrai);
void	thcke_fd(t_data *data, int fd);
void	ft_closse(t_redir *redir, int fd);
void	ft_tchek_herdok(t_redir *redir);
void	ft_erorr(char *str);
=======
	t_data	*current;
	t_data	*next;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;
}	t_var_data;

int			check_quotes(char *line, int i, int count_quote);
t_token		*lexing(char *line, int *flag, t_listenv *head);

int			sp(char c);
t_token		*tokenization(char *line, int i);
void		handle_quotes(t_quote_data *data, t_initalize *init);

void		free_tokens(t_token *tokens);
t_token		*deldum(t_token **head);
void		free_data(t_data *data);

int			error(t_token *tokens, t_token *current);
int			is_redirect(t_keyword type);
int			is_pipe(t_keyword type);
int			pipe_check(t_token *prev, t_token *next);

void		ft_expand(t_token *tokens, int i, t_listenv *head);
void		handle_single_quote(t_expand *ex, t_token *tokens);
void		process_dollar(t_expand *ex,
				t_token *tokens, t_listenv *head, t_tg *data);
void		handle_odd_dollars(t_expand *ex,
				t_token *tokens, t_listenv *head, t_tg *data);
void		extract_var(t_expand *ex, char *str);
void		append_char(t_expand *ex, char c);
void		handle_num(t_expand *ex, t_token *tokens);
void		handle_status(t_expand *ex, int status);

void		ft_rename(t_token *tokens);

int			ft_herdoc(t_token **tokens, t_listenv *head);
char		**ft_expand_herdoc(char *str, int *flag, t_listenv *head);
void		handle_odd_dollars_herdoc(t_expand *ex, char *str,
				int *flag, t_listenv *head);
void		extract_var_herdoc(t_expand *ex, char *str);
void		append_char_herdoc(t_expand *ex, char c);
int			check_delimter(char *delimter);
char		*generate_name(void);
char		*get_word(int fd);

t_data		*parsing(t_token **tokens, t_token *temp);
t_data		*ft_lstnew_p(void);

char		*ft_substr(char *s, int start, int len);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *s);
char		*ft_strdup(char *s);
int			ft_isprint(int c);
int			ft_cmp(char *word);
char		*ft_strjoin(char *s1, char *s2);
t_token		*ft_lstnew(char *content, t_keyword type);
void		ft_lstadd_back(t_token **lst, t_token *new);

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
void		*ft_memset(void *b, int c, size_t len);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);

void		*ft_free(char **strs, int count);
char		**ft_split(char *s, char c);
int			word_count(char *s, char c);

int			ft_open_herdoc_until_error(t_token *current, t_listenv *head);

void		ft_ambigous(char *env_name,
				t_expand *ex, t_tg *data, t_token *tokens);

t_listenv	*ft_lstnew_env(char *content, char *path);

void		ft_lstadd_back_ex(t_listenv **lst, t_listenv *new);
void		ft_lstdelone(t_listenv *lst, void (*del)(void *));
int			ft_lstsize(t_listenv *lst);
int			ft_env(char **env, t_listenv **head);
int			ft_tchc_data(t_data *data, t_listenv **head);
int			ft_pwd(t_listenv *head);
int			ft_echo(t_data *data);
int			ft_unset(t_data *data, t_listenv **head);
int			ft_exit(t_data *data);
int			ft_cd(t_data *data, t_listenv *head);
int			ft_export(t_listenv **head, t_data *data);
int			thcking_pluss(char *str);
int			tchking_egal(char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_tchk_cotachen(char *s1);
char		**ft_ar_env(t_listenv *head);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
int			ft_execoshen(t_data *data, t_listenv **head);
int			ft_strncmp(char *s1, char *s2, int n);
char		*get_command_path(char *commnd, char **ary_envp, int *status);
char		*ft_strcpy(char *dst, const char *src);
int			ft_isalpha(int c);
void		ft_lstclear(t_listenv **lst, void (*del)(void *));

int			is_builtin(t_data *data, t_listenv **head);
t_listenv	*tcchk_untel_egall(char *data, t_listenv *head);
int			tcchk_untel_egll(char *data, t_listenv *head);
int			ft_tchck_argmo_exat(char *data);
void		tchek_only_key(char *data, t_expcall *call, t_listenv **head);
void		free_copy_listenv(t_listenv *head);
void		separe_egal_pluss(t_data *data, t_expcall *call, t_listenv **head);

void		extract_name_and_value(char *arg, char **name, char **value);

t_listenv	*find_variable(t_listenv *head, char *name);
int			find_varble(t_listenv *head, char *name);
int			ft_lstsize_data(t_data *lst);
void		*ft_free(char **strs, int count);
int			ft_tchee_redercter(t_data *data, t_listenv **head);
void		ft_closse(t_redir *redir, int fd);
void		ft_free_ex(char **str);
void		function_call(t_listenv **head, t_data *data);
void		only_key(char *data, char **splt_plus, t_listenv **head);
void		cleanup_memory(char *splt_egal, char **splt_plus, char *segal);
void		my_del(void *ptr);
char		*ft_strdup_unset(char *s);
int			ft_tchk_value(char *data);
t_listenv	*copy_listenv(t_listenv *head);
void		pluss_egal(t_data *data, int x, t_listenv *head, char *segal);
void		extract_name_and_value(char *arg, char **name, char **value);
int			ft_strlen_name(int *i, char *arg);
void		ft_egal_pacslash(t_data *data,
				char *splt_egal, char **splt_plus, t_listenv *head);
void		pluss_egal_pacslash(t_data *data,
				int x, t_listenv **head, char *segal);
char		*store_pwd(char *str, int flag);
void		ft_freee(char **arrai);
void		thcke_fd(t_data *data, int fd);
void		ft_closse(t_redir *redir, int fd);
void		ft_tchek_herdok(t_redir **redir);
void		ft_erorr(char *str);
int			ft_tchee_redercter(t_data *data, t_listenv **head);
void		ft_tchk_not_peltend(t_data *data,
				char **env_ar, char *cmd_path, int *status);
int			ft_tchck_status(int status);
int	print_env(t_listenv *head);
int last_status(int value, int mod);
>>>>>>> 4989a159ff5b68e0f418d102a2ac2aa750f09dca

#endif