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
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HDOC,
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

typedef struct s_token
{
	char 			*value;
	t_tokent	 	type;
	struct s_token	*next;
}					t_token;

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

#endif