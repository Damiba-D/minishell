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

typedef	enum	e_tokent
{
	WORD,
	PIPE, // |
	REDIN, // <
	REDOUT, // >
	APPEND, // >>
	HDOC, // <<
}		t_tokent;

typedef struct	s_input
{
	char			**argv; // list of args
	char			*infile; // < cmd
	char			*outfile; // > cmd
	int				append; // >> cmd
	int				hdoc; // << cmd
	struct s_input	*next; // proximo pipe
}					t_input;

typedef struct	s_msh
{
	t_input	*imput;
	char	*rline;
	char	*prompt;
	int		error_status;
}			t_msh;

t_input	*create_input_node(char *segment);
void	add_input_back(t_input **lst, t_input *new);
t_input	*parse_line(char *line);


t_msh	*msh(void);
void	free_arr(char **arr);
void	free_input_list(t_input *input_list);

// utils
int	skip_whitespace(char *str, int pos);
int	skip_reds_filename(char *seg, int start_pos);

// extract_reds
char	*ext_reds_file(char *seg, t_tokent type);
char	*ext_reds_file_util(char *seg, int start_pos);

// free hub
char	*remove_all_reds(char *seg);


// check_reds
int	find_in_red(char *seg, int start_pos);
int	find_out_red(char *seg, int start_pos);
int	find_hdoc(char *seg, int start_pos);
int	find_append(char *seg, int start_pos);
int	find_next_red(char *seg, int start_pos);

#endif