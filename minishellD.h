
#ifndef MINISHELLD_H
# define MINISHELLD_H

# include "libft/libft.h"
# include "export_cmd/export_cmd.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <linux/limits.h>
# include <stdbool.h>

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}   t_env;


void	free_arr(char **arr);
void	exit_cmd(t_env *env_list, unsigned char exit_code);
void	malloc_err_exit(t_env *env_list, char *err_loc);
t_env	*env_new_node(char *key, char *value);
void	env_add(t_env **lst, t_env *new);
t_env	*get_env_node(char *key, t_env *env_list);
char	*get_env_value(const char *key, t_env *env_list);
void	set_env_value(const char *key, const char *value, t_env **env_list, bool append);
void	free_env_node(t_env *env_node);
int		env_lstsize(t_env *lst);
char	**env_list_to_char(t_env *env_list);
void	unset_env(const char *key, t_env **env_list);
void	init_env(t_env **env_list);
void	term_env(t_env *env_list);
int		env_cmd(t_env *env_list);
int		echo_cmd(char **argv);
int		unset_cmd(char **args, t_env **env_list);
int		pwd_cmd(t_env *env_list);

#endif