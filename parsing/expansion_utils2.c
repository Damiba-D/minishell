#include "../minishell.h"

int	handle_dollar_sign(char *str, int *i, int *var_start, int *var_end)
{
	char	*var_name;

	*var_start = *i;
	(*i)++;
	var_name = extract_var_name(str, i);
	if (var_name)
	{
		*var_end = *i;
		free(var_name);
		return (1);
	}
	return (0);
}

int	find_next_var(char *str, int start, int *var_start, int *var_end)
{
	int		i;
	int		in_single;
	int		in_double;

	if (!str || start < 0)
		return (0);
	i = start;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		update_quotes(str[i], &in_single, &in_double);
		if(str[i] == '$' && !in_single)
		{
			if (handle_dollar_sign(str, &i, var_start, var_end))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
char	*replace_var_str(char *str, int var_start, int var_end, char *value)
{
	int		new_len;
	char	*res;
	int		value_len;
	int		str_len;

	if (!str || !value)
		return (NULL);
	str_len = ft_strlen(str);
	if (var_start < 0 || var_end <= var_start || var_end > str_len)
		return (ft_strdup(str));
	value_len = ft_strlen(value);
	new_len = str_len - (var_end - var_start) + value_len;
	res = malloc(new_len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	if (var_start > 0)
		ft_strlcpy(res, str, var_start + 1);
	ft_strlcat(res, value, new_len + 1);
	if (str[var_end])
		ft_strlcat(res, str + var_end, new_len + 1);
	return (res);
}
