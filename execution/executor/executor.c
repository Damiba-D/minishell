#include "../../minishell.h"
#include "executor.h"

void wait_children(int last_pid)
{
	int i;
	int w_status;
	int sig;

	i = 0;
	if (!msh()->pids)
		return ;
	while (i < last_pid)
	{
		if (msh()->pids[i] > 0)
			waitpid(msh()->pids[i], &w_status, 0);
		i++;
	}
	if (WIFEXITED(w_status))
		msh()->last_exit_status = WEXITSTATUS(w_status);
	else if (WIFSIGNALED(w_status))
	{
		sig = WTERMSIG(w_status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		msh()->last_exit_status = 128 + sig;
	}
	free(msh()->pids);
	msh()->pids = NULL;
}

void	executor(void)
{
	t_input *temp;
	int input_size;

	temp = (t_input *)msh()->inputlst->content;
	if (!temp->argv[0])
		return (ft_lstclear(&msh()->inputlst, free_input_node));
	input_size = ft_lstsize(msh()->inputlst);
	setup_execution_signals();
	if (input_size == 1)
	{
		exe_hds(temp);
		if (is_builtin(temp->argv[0]))
			execute_builtin(temp);
		else
			execute_ext_cmd(temp);
	}
	else
		execute_pipeline(input_size);
	wait_children(input_size);
	setup_execution_signals();
	ft_lstclear(&msh()->inputlst, free_input_node);
}
