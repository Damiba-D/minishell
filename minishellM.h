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

typedef struct	s_cmd
{
	char			**argv; // list of args
	char			*infile; // < cmd
	char			*outfile; // > cmd
	int				append; // >> cmd
	int				hdoc; // < cmd
	struct s_cmd	*next; // proximo pipe
}					t_cmd;

t_cmd	*data(void);
void	free_arr(char **arr);

#endif