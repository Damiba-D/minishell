#include "../../minishell.h"

static int	find_next_var_hdoc(char *str, int last_end, int *var_start, int *var_end)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!str || last_end < 0)
		return (0);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		update_quotes(str[i], &in_single, &in_double);
		if (str[i] == '$' && i >= last_end)
		{
			if ((str[i + 1] == '\0' || str[i + 1] == ' '
				|| str[i + 1] == '\''
				|| str[i + 1] == '\"') && ++i)
				continue ;
			if (handle_dollar_sign(str, &i, var_start, var_end))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	*replace_next_var_hdoc(char *result, int *last_end)
{
	char	*new_result;
	int		var_pos[2];

	if (!find_next_var_hdoc(result, *last_end, &var_pos[0], &var_pos[1]))
		return (result);
	new_result = process_single_var(result, var_pos[0], var_pos[1]);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	*last_end = calc_next_srch_pos(result, new_result, var_pos[0], var_pos[1]);
	free(result);
	return (new_result);
}

char	*hdoc_expand_arg(char *line)
{
	char	*result;
	char	*new_result;
	int		last_replaced_end;

	if (!line)
		return (NULL);
	result = ft_strdup(line);
	if (!result)
		return (NULL);
	last_replaced_end = 0;
	while (result)
	{
		new_result = replace_next_var_hdoc(result, &last_replaced_end);
		if (new_result == result)
			break ;
		if (!new_result)
			return (free(result), ft_strdup(""));
		result = new_result;
	}
	return (result);
}