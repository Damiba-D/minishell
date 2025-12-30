#include "../minishell.h"

void	signal_handler(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		msh()->last_exit_status = 130;
	}
}

void	signal_handler_pipe(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
		msh()->last_exit_status = 130;
	else if (signal == SIGQUIT)
		msh()->last_exit_status = 131;
}

void	signal_handler_hdoc(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		msh()->last_exit_status = 130;
	}
}

void	signal_handler_hparent(int signum)
{
	(void)signum;
	msh()->last_exit_status = 130;
}
