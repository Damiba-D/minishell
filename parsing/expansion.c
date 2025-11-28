#include "../minishell.h"

static int	is_var_char(char c)
{
	return(ft_isalnum(c) || c == '_');
}

static void	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

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
