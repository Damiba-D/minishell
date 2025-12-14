#include "../../minishell.h"
#include "executor.h"

bool is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "env", 4))
		return (true);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (true);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (true);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (true);
	else if (!ft_strncmp(cmd, "export", 7))
		return (true);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (true);
	return (false);
}

int run_builtin(t_input *input)
{
	char	*cmd;

	cmd = input->argv[0];
	if (!ft_strncmp(cmd, "env", 4))
		return (env_cmd());
	else if (!ft_strncmp(cmd, "echo", 5))
		return (echo_cmd(input->argv));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (unset_cmd(input->argv));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd_cmd(input->argv));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (cd_cmd(input->argv));
	else if (!ft_strncmp(cmd, "export", 7))
		return (export_cmd(input->argv));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (exit_cmd(input->argv));
	return (0);
}

void execute_builtin(t_input *input)
{
	if (setup_fds(input, msh()->og_fds, true))
		return (restore_fds(msh()->og_fds));
	msh()->last_exit_status = run_builtin(input);
	restore_fds(msh()->og_fds);
}
