#ifndef EXECUTOR_H
#include "../../parsing/parsing.h"
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
void	cleanup_failed_pipeline(int prev_read);
void	pipeline_process(t_list *current);
void	execute_pipeline(t_list *inputlst, int input_size);
void	wait_children(int last_pid);
void	executor(void);
void	restore_fds(int *fd);
#endif