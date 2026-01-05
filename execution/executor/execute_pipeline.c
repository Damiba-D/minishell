#include "../../minishell.h"
#include "executor.h"

void cleanup_failed_pipeline(char *error, int prev_read)
{
	int i;
	int w_status;

	i = 0;
	print_err(NULL, error, true);
	while (msh()->pids[i] > 0)
	{
		waitpid(msh()->pids[i], &w_status, 0);
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	msh()->last_exit_status = 1;
	free(msh()->pids);
	msh()->pids = NULL;
}

void pipeline_process(t_list *current)
{
	t_input *node;
	char *cmd;
	char **env;

	node = (t_input *)current->content;
	if (setup_fds(node, msh()->og_fds, false))
		error_exit(NULL, NULL, 1, false);
	if (is_builtin(node->argv[0]))
		error_exit(NULL, NULL, run_builtin(node), false);
	else
	{
		cmd = cmd_create(node);
		env = env_list_to_char(msh()->env);
		if (!env)
			error_exit("malloc", "Allocation Error", 1, false);
		if (execve(cmd, node->argv, env))
		{
			free(cmd);
			free_arr(env);
			error_exit(NULL, node->argv[0], 1, true);
		}
	}
}

static void setup_child(int cmd_no, int input_size)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	save_og_fds(msh()->og_fds);
	if (msh()->prev_read != -1)
	{
		dup2(msh()->prev_read, STDIN_FILENO);
		close(msh()->prev_read);
	}
	if (cmd_no < input_size - 1)
	{
		close(msh()->pipe[0]);
		dup2(msh()->pipe[1], STDOUT_FILENO);
		close(msh()->pipe[1]);
	}
}

static void execute_and_reset(t_list *current, int cmd_no, int input_size)
{
	if (msh()->pids[cmd_no] == 0)
	{
		setup_child(cmd_no, input_size);
		pipeline_process(current);
	}
	if (msh()->prev_read != -1)
		close(msh()->prev_read);
	if (cmd_no < input_size - 1)
	{
		close(msh()->pipe[1]);
		msh()->prev_read = msh()->pipe[0];
	}
}

void execute_pipeline(int input_size)
{
	int i;
	t_list *current;	

	i = 0;
	current = msh()->inputlst;
	msh()->pids = malloc(sizeof(pid_t) * input_size);
	if (!msh()->pids)
		error_exit("malloc", "Allocation Error", 1, false);
	while (current)
	{
		exe_hds((t_input *)current->content);
		if (i < input_size - 1 && pipe(msh()->pipe) == -1)
			return (cleanup_failed_pipeline("pipe", msh()->prev_read));
		msh()->pids[i] = fork();
		if (msh()->pids[i] == -1)
		{
			if (i < input_size - 1)
				close_pipe();
			return (cleanup_failed_pipeline("fork", msh()->prev_read));
		}
		execute_and_reset(current, i, input_size);
		current = current->next;
		i++;
	}
}
