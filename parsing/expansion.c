#include "../minishell.h"

static char	*exp_single_var(char *var_name, t_env *env_list, int lst_exit_stat)
{
	char	*value;

	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(lst_exit_stat));
	value = get_env_value(var_name, env_list);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
