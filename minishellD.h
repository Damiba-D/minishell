
#ifndef MINISHELLD_H
# define MINISHELLD_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}   t_env;


t_env	*env_new_node(char *key, char *value);
void	env_add(t_env **lst, t_env *new);
void	init_env(t_env **env_list);
int		env_cmd(t_env *env_list);

#endif