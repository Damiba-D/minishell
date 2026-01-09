#include "../../minishell.h"
#include "executor.h"

/*
** ============================================================
**  EXEC DESCRIPTOR
**  Built entirely in the parent before fork()
** ============================================================
*/

typedef struct s_exec
{
	char	*cmd_path;
	char	**argv;
	t_input	*node;
	int		is_builtin;
}	t_exec;

/*
** ============================================================
**  PARENT-ONLY: resolve executable path
** ============================================================
*/

static char	*resolve_command(t_input *node)
{
	char	*cmd;

	if (!node || !node->argv || !node->argv[0])
		return (NULL);
	cmd = cmd_create(node);
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) != 0)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

/*
** ============================================================
**  PARENT-ONLY: build execution table
** ============================================================
*/

static t_exec	*build_exec_table(t_list *lst, int count)
{
	t_exec	*execs;
	int		i;

	execs = malloc(sizeof(t_exec) * count);
	if (!execs)
		return (NULL);
	i = 0;
	while (i < count && lst)
	{
		execs[i].node = (t_input *)lst->content;
		execs[i].argv = execs[i].node->argv;
		execs[i].is_builtin = is_builtin(execs[i].argv[0]);
		if (execs[i].is_builtin)
			execs[i].cmd_path = NULL;
		else
			execs[i].cmd_path = resolve_command(execs[i].node);
		lst = lst->next;
		i++;
	}
	return (execs);
}

/*
** ============================================================
**  CHILD: pipe wiring only
** ============================================================
*/

static void	child_setup_pipes(int index, int count,
								int prev_read, int pipefd[2])
{
	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (index < count - 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

/*
** ============================================================
**  CHILD: execute command (NO MALLOC, NO FREE)
** ============================================================
*/

static void	child_execute(t_exec *exec, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (setup_fds(exec->node, NULL, false))
		_exit(1);

	if (exec->is_builtin)
		_exit(run_builtin(exec->node));

	execve(exec->cmd_path, exec->argv, envp);
	_exit(127);
}

/*
** ============================================================
**  PARENT: close pipe ends
** ============================================================
*/

static void	parent_close_pipes(int *prev_read,
								int pipefd[2],
								int index,
								int count)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (index < count - 1)
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
}

/*
** ============================================================
**  MAIN ENTRY POINT
** ============================================================
*/

void	execute_pipeline(t_list *lst, int count)
{
	t_exec	*execs;
	char	**envp;
	pid_t	*pids;
	int		pipefd[2];
	int		prev_read;
	int		status;
	int		i;

	if (!lst || count <= 0)
		return ;

	execs = build_exec_table(lst, count);
	if (!execs)
		return ;

	envp = env_list_to_char(msh()->env);
	if (!envp)
	{
		free(execs);
		return ;
	}

	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
	{
		free(envp);
		free(execs);
		return ;
	}

	prev_read = -1;
	i = 0;
	while (i < count)
	{
		if (i < count - 1)
		{
			if (pipe(pipefd) == -1)
				break ;
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			child_setup_pipes(i, count, prev_read, pipefd);
			child_execute(&execs[i], envp);
		}
		parent_close_pipes(&prev_read, pipefd, i, count);
		i++;
	}

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			msh()->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			msh()->last_exit_status = 128 + WTERMSIG(status);
		i++;
	}

	i = 0;
	while (i < count)
	{
		if (execs[i].cmd_path)
			free(execs[i].cmd_path);
		i++;
	}
	free(execs);
	free(envp);
	free(pids);
}
