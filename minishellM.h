#ifndef MINISHELLM_H
# define MINISHELLM_H

# include "libft/libft.h"
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

t_data	*minsh(void);

#endif