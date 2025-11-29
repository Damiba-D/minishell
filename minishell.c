#include "minishell.h"

int	main(void)
{
	init_env(&msh()->env);
	msh()->last_exit_status = 0;
	setup_interactive_signals();
	while (1)
	{
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
