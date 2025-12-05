#ifndef EXECUTOR_H
#include "../../parsing/parsing.h"
bool is_builtin(char *cmd);
int run_builtin(t_input *input);
void exe_hds(t_input *input);
void open_file(char *name, int *fd, t_token type);
char	*parse_infiles(t_input *input, int *flag, int *fd);
char *parse_outfiles(t_input *input, int *fd, int *flag);
void execute_builtin(t_list *input_node);
void	executor(void);
#endif