/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:47:53 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:47:54 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "shared.h"
# include "parsing/parsing.h"
# include "execution/execution.h"

# define HEREDOC "/tmp/minishell-heredoc-"
# define H_D_LEN 23

typedef struct s_msh
{
	t_env	*env;
	t_list	*inputlst;
	char	*cmdline;
	int		last_exit_status;
	int		og_fds[2];
	pid_t	*pids;
	int		pipe[2];
	int		prev_read;
	bool	hdoc_stop;
	bool	is_child;
}			t_msh;

t_msh	*msh(void);

#endif