#include "../minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_execution(int sig)
{
    (void)sig;
    printf("\n");
}

void	handle_sigquit_interactive(int sig)
{
    (void)sig;
}

void	setup_interactive_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, handle_sigquit_interactive);
}

// Setup signals for command execution
void	setup_execution_signals(void)
{
    signal(SIGINT, handle_sigint_execution);
    signal(SIGQUIT, SIG_DFL);
}

/* void	signal_main(void)
{
	static struct sigaction	sig;


} */