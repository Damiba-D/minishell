/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:46:02 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:46:03 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../parsing/parsing.h"

bool	is_builtin(char *cmd);
int		run_builtin(t_input *input);
void	exe_hds(t_input *input);
void	open_file(char *name, int *fd, t_token type);
char	*parse_infiles(t_input *input, int *flag, int *fd);
char	*parse_outfiles(t_input *input, int *fd, int *flag);
void	save_og_fds(int *og_fd);
int		setup_fds(t_input *input, int *og_fd, bool save);
void	execute_builtin(t_input *input);
char	*find_command(t_input *input, char *path);
char	*cmd_create(t_input *input);
void	execute_ext_cmd(t_input *input);
void	cleanup_failed_pipeline(char *error, int prev_read);
void	pipeline_process(t_list *current);
void	execute_pipeline(int input_size);
void	wait_children(int last_pid);
void	executor(void);
void	restore_fds(int *fd);
void	close_pipe(void);
bool	execute_all_hds(t_list *input);
char	*replace_next_var_hdoc(char *result, int *last_end);
char	*hdoc_expand_arg(char *line);

#endif