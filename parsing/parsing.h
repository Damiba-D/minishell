#ifndef PARSING_H
# define PARSING_H

# include "../shared.h"
# include "arg_split.h"

typedef struct s_env t_env;
typedef struct s_msh t_msh;

typedef enum e_token
{
	REDIN, // <
	REDOUT, // >
	HDOC, // <<
	APPEND, // >>
}	t_token;

typedef struct s_file
{
	char	*filename;
	t_token	mode;
	bool	quoted;
}			t_file;

typedef struct s_input
{
	char	**argv;
	t_file	*infiles;
	t_file	*outfiles;
}			t_input;

t_input	*create_input_node(char *segment);
t_list	*parse_line(char *line);

// utils
int		skip_whitespace(char *str, int pos);
int		skip_reds_filename(char *seg, int start_pos);
void	update_quotes(char c, int *in_quote, int *in_dquote);
int		count_pipes(char *line);

// extract_reds
void	ext_reds_file(char *seg, t_input *node);
void	ext_reds_file_single(char *seg, int *i, t_input *node, int *red_i);
char	*ext_reds_file_util(char *seg, int *i, bool *quoted);

// free hub
char	*remove_all_reds(char *seg);
void	free_arr(char **arr);
void	free_file_arr(t_file *files);
void	free_input_node(void *content);
void	free_all(char **segments, t_list **input_list, t_list *new_node);

// signals (temporary)
void	signal_handler(int sig);
void	handle_sigint_execution(int sig);
void	handle_sigquit_interactive(int sig);
void	setup_interactive_signals(void);
void	setup_execution_signals(void);

// expansions
int		is_var_char(char c);
void	*extract_var_name(char *str, int *i);
char	*exp_var_env(char *var_name, t_env *env_list, int lst_exit_stat);
int		handle_dollar_sign(char *str, int *i, int *var_start, int *var_end);
int		find_next_var(char *str, int last_end, int *var_start, int *var_end);
char	*replace_var_str(char *str, int var_start, int var_end, char *value);
int		calc_next_srch_pos(char *old, char *new, int var_start, int var_end);
char	*replace_next_var(char *result, int *last_end);
char	*process_single_var(char *result, int var_start, int var_end);
char	*expand_arg(char *arg);
void	expand_all(t_msh *msh_data);

// quote_removal
void	remove_quotes_input(t_input *node);

// refactoring
char    **append_arrays(char **dst, char **src);
char	**resplit_after_expansion(char **argv);

#endif