#include "../minishell.h"

int	is_var_char(char c)
{
	return(ft_isalnum(c) || c == '_');
}

void	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	if (!str || !i)
		return (NULL);
	start = *i;
	len = 0;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && is_var_char(str[*i]))
	{
		(*i)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	return (var_name);
}

char	*exp_var_env(char *var_name, t_env *env_list, int lst_exit_stat)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(lst_exit_stat));
	value = get_env_value(var_name, env_list);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*process_single_var(char *result, int var_start, int var_end)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	if (!result || var_start < 0 || var_end <= var_start)
		return (NULL);
	var_name = ft_substr(result, var_start + 1, var_end - var_start - 1);
	if (!var_name)
		return (NULL);
	var_value = exp_var_env(var_name, msh()->env, msh()->last_exit_status);
	free(var_name);
	if (!var_value)
		return (ft_strdup(result));
	new_result = replace_var_str(result, var_start, var_end, var_value);
	free(var_value);
	return (new_result);
}