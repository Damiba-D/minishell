#include "../../minishell.h"
#include "executor.h"

void	executor(void)
{
	t_input *temp;
	bool wait_child;
	int input_size;

	temp = (t_input *)msh()->inputlst->content;
	wait_child = false;
	input_size = ft_lstsize(msh()->inputlst);
	if (input_size == 1)
	{
		if (is_builtin(temp->argv[0]))
			execute_builtin(temp);
		else
			execute_ext_cmd(temp);
	}
	else
	{
		execute_pipeline(msh()->inputlst, input_size);
		wait_child = true;
	}
	if (wait_child)
		wait_children(input_size);
	ft_lstclear(&msh()->inputlst, free_input_node);
}
