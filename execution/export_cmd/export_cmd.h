#ifndef EXPORT_CMD_H
# define EXPORT_CMD_H

typedef struct s_env t_env;

int		env_keycmp(const char *s1, const char *s2);
void	sort_env_array(t_env **env);
int		is_invalid_identifier(char *arg, int *ret_val);
t_env	**lst_to_arr(t_env *env_list);
int		export_cmd(char **args);

#endif