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

typedef struct	s_input
{
	char			**argv; // list of args
	char			*infile; // < cmd
	char			*outfile; // > cmd
	int				append; // >> cmd
	int				hdoc; // << cmd
	struct s_input	*next; // proximo pipe
	struct s_input	*prev;
}					t_input;

typedef struct	s_msh
{
	t_input	*imput;
	char	*rline;
	char	*prompt;
	int		error_status;
}			t_msh;


t_msh	*msh(void);
void	free_arr(char **arr);

#endif