#ifndef MINISHELLM_H
# define MINISHELLM_H

# include "libft/libft.h"
# include "parsing/arg_split.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <stdbool.h>

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
	char		**argv;
	t_file		*infiles;
	t_file		*outfiles;
}					t_input;

typedef struct s_msh
{
	t_input	*input;
	char	*rline;
	char	*prompt;
	int		exit_status;
}			t_msh;

t_input	*create_input_node(char *segment);
t_list	*parse_line(char *line);

t_msh	*msh(void);

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


#endif