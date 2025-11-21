#include "../minishell.h"

static int execute_builtin(t_list *input_node)
{
	t_input	*input;
	char	*cmd;

	input = (t_input *)input_node->content;
	cmd = input->argv[0];
	//Save standard FDs
	if (!ft_strncmp(cmd, "env", 4))
		msh()->last_exit_status = env_cmd();
	else if (!ft_strncmp(cmd, "echo", 5))
		msh()->last_exit_status = echo_cmd(input->argv);
	else if (!ft_strncmp(cmd, "unset", 6))
		msh()->last_exit_status = unset_cmd(input->argv);
	else if (!ft_strncmp(cmd, "pwd", 4))
		msh()->last_exit_status = pwd_cmd(input->argv);
	else if (!ft_strncmp(cmd, "cd", 3))
		msh()->last_exit_status = cd_cmd(input->argv);
	else if (!ft_strncmp(cmd, "export", 7))
		msh()->last_exit_status = export_cmd(input->argv);
	else if (!ft_strncmp(cmd, "exit", 5))
		msh()->last_exit_status = exit_cmd(input->argv);
	else
		return (0);
	return (1);
	
	//Restore FDs
}

void	executor(void)
{
	t_list *temp;

	temp = msh()->inputlst;
	if (execute_builtin(temp))
	{
		ft_lstclear(&msh()->inputlst, free_input_node);
		return ;
	}
}
