#ifndef MINISHELL_H
# define MINISHELL_H

# include "shared.h"
# include "parsing/parsing.h"
# include "execution/execution.h"

typedef struct s_msh
{
	t_env	*env;
	t_list	*inputlst;
	char	*cmdline;
	int		last_exit_status;
	int		og_fds[2];
	pid_t	*pids;
	int		pipe[2];
	int		prev_read;
}			t_msh;

t_msh	*msh(void);

#endif