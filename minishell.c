/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:47:47 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 18:18:01 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(void)
{
	msh()->last_exit_status = 0;
	msh()->pids = NULL;
	init_env(&msh()->env);
	msh()->is_child = false;
}

static void	reset(void)
{
	msh()->prev_read = -1;
	msh()->og_fds[0] = -1;
	msh()->og_fds[1] = -1;
	msh()->hdoc_stop = false;
}

static void	remove_loop_q(void)
{
	t_list	*cur;

	cur = msh()->inputlst;
	while (cur)
	{
		remove_quotes_input((t_input *)cur->content);
		cur = cur->next;
	}
}

static int	read_input(void)
{
	msh()->cmdline = readline("minishell$ ");
	if (!msh()->cmdline)
		exit_cmd(NULL);
	if (!msh()->cmdline[0])
	{
		free(msh()->cmdline);
		return (0);
	}
	add_history(msh()->cmdline);
	return (1);
}

int	main(void)
{
	init();
	while (1)
	{
		reset();
		setup_interactive_signals();
		if (!read_input())
			continue ;
		if (check_syntax(msh()->cmdline))
		{
			msh()->last_exit_status = 2;
			free(msh()->cmdline);
			continue ;
		}
		msh()->inputlst = parse_line(msh()->cmdline);
		if (!msh()->inputlst)
		{
			free(msh()->inputlst);
			continue ;
		}
		expand_all(msh());
		remove_loop_q();
		executor();
		free(msh()->cmdline);
	}
	return ((unsigned char)msh()->last_exit_status);
}
