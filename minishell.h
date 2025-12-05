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
}			t_msh;

t_msh	*msh(void);

#endif