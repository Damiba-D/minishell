#ifndef MINISHELL_H
# define MINISHELL_H
# include "shared.h"
# include "execution/execution.h"
# include "parsing/parsing.h"

typedef struct s_msh
{
	t_input	*input;
	char	*rline;
	char	*prompt;
	int		exit_status;
}			t_msh;

t_msh	*msh(void);

#endif