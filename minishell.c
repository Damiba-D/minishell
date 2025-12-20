#include "minishell.h"

int	main(void)
{
	msh()->last_exit_status = 0;
	msh()->pids = NULL;
	init_env(&msh()->env);
	setup_interactive_signals();
	while (1)
	{
		msh()->prev_read = -1;
		msh()->og_fds[0] = -1;
		msh()->og_fds[1] = -1;
		setup_interactive_signals();
		msh()->cmdline = readline("minishell$ ");
		if (!msh()->cmdline)
            exit_cmd(NULL);
		if (!msh()->cmdline[0])
		{
			free(msh()->cmdline);
			continue ;
		}
		add_history(msh()->cmdline);
		msh()->inputlst = parse_line(msh()->cmdline);
		if (!msh()->inputlst)
		{
			free(msh()->inputlst);
			continue ;
		}
		expand_all(msh());
		t_list *cur = msh()->inputlst;
		while (cur)
		{
			remove_quotes_input((t_input *)cur->content);
			cur = cur->next;
		}
		setup_execution_signals();
		executor();
        free(msh()->cmdline);
	}
	return ((unsigned char)msh()->last_exit_status);
}
