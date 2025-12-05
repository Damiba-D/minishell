
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include "../shared.h"
# include "export_cmd/export_cmd.h"
# include "executor/executor.h"
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

void	free_arr(char **arr);
int		exit_cmd(char **args);
void	print_err(char *context, char *detail, bool err);
void	error_exit(char *context, char *detail, int exit_code, bool err);
t_env	*env_new_node(char *key, char *value);
void	env_add(t_env **lst, t_env *new);
t_env	*get_env_node(char *key, t_env *env_list);
char	*get_env_value(const char *key, t_env *env_list);
void	set_env_value(const char *key, const char *value, t_env **env_list, bool append);
void	free_env_node(t_env *env_node);
int		env_lstsize(t_env *lst);
char	**env_list_to_char(t_env *env_list);
void	init_env(t_env **env_list);
void	term_env(t_env *env_list);
int		env_cmd(void);
int		echo_cmd(char **argv);
int		unset_cmd(char **args);
int		pwd_cmd(char **args);
int		cd_cmd(char **args);
void	executor(void);
void	here_doc_handler(t_file *here_doc);

#endif