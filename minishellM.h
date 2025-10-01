#ifndef MINISHELLM_H
# define MINISHELLM_H

# include "libft/libft.h"
# include "arg_split/arg_split.h"
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

typedef struct	s_data
{
	char	*rline;
	char	*prompt;
	int		signal;


}		t_data;

t_data	*data(void);
void	free_arr(char **arr);


#endif