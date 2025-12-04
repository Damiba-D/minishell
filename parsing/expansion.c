#include "../minishell.h"

static char	*process_single_var(char *result, int var_start, int var_end)
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

char	*expand_arg(char *arg)
{
	char	*result;
	char	*new_result;
	int		var_pos[2];
	int		search_pos;

	if (!arg)
		return (NULL);
	result = ft_strdup(arg);
	search_pos = 0;
	while (find_next_var(result, search_pos, &var_pos[0], &var_pos[1]))
	{
		new_result = process_single_var(result, var_pos[0], var_pos[1]);
		if (!new_result)
			break;
		search_pos = var_pos[0];
		free(result);
		result = new_result;
	}
	if (!result)
		result = ft_strdup("");
	return (result);
}

void	expand_args(t_input *node)
{
	int		i;
	char	*expanded;
	char	*original;

	if (!node || !node->argv)
		return ;
	i = 0;
	while (node->argv[i])
	{
		original = node->argv[i];
		expanded = expand_arg(original);
		if (expanded)
		{
			node->argv[i] = expanded;
			free(original);
		}
		else
		{
			node->argv[i] = ft_strdup("");
			free(original);
		}
		i++;
	}
}

void	expand_all(t_msh *msh)
{
	t_list	*current;
	t_input	*node;

	if (!msh)
		return ;
	current = msh->inputlst;
	while (current)
	{
		node = (t_input *)current->content;
		expand_args(node);
		current = current->next;
	}
}
