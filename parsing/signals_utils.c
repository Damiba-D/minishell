/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:54 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:55 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	signal_handler_hdoc(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		msh()->hdoc_stop = true;
		close(STDIN_FILENO);
		msh()->last_exit_status = 130;
	}
}
