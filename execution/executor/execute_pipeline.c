#include "../../minishell.h"
#include "executor.h"

void cleanup_failed_pipeline(int prev_read)
{
	int i;
	int w_status;

	i = 0;
	print_err(NULL, "fork", true);
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
	
	setup_fds(node, msh()->og_fds, false);
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

void execute_pipeline(t_list *inputlst, int input_size)
{
	int i;
	t_list *current;

	i = 0;
	current = inputlst;
	msh()->pids = malloc(sizeof(pid_t) * input_size);
	if (!msh()->pids)
		error_exit("malloc", "Allocation Error", 1, false);
	while (current)
	{
		if (i < input_size - 1 && pipe(msh()->pipe) == -1)
		{
			if (msh()->prev_read != -1)
				close(msh()->prev_read);
			cleanup_failed_pipeline(msh()->prev_read);
		}
		msh()->pids[i] = fork();
		if (msh()->pids[i] == -1)
		{
			if (i < input_size)
			{
				close(msh()->pipe[0]);
				close(msh()->pipe[1]);
			}
			cleanup_failed_pipeline(msh()->prev_read);
			return ;
		}
		if (msh()->pids[i] == 0)
		{
			save_og_fds(msh()->og_fds);
			if (msh()->prev_read != -1)
			{
				dup2(msh()->prev_read, STDIN_FILENO);
				close(msh()->prev_read);
			}
			if (i < input_size - 1)
			{
				close(msh()->pipe[0]);  // Close read end
				dup2(msh()->pipe[1], STDOUT_FILENO);
				close(msh()->pipe[1]);
			}
			pipeline_process(current);
		}
		if (msh()->prev_read != -1)
			close(msh()->prev_read);
		
		// Close current pipe write end and save read end
		if (i < input_size - 1)
		{
			close(msh()->pipe[1]);
			msh()->prev_read = msh()->pipe[0];  // Save for next iteration
		}
		current = current->next;
		i++;
	}
}
