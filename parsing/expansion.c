#include "../minishell.h"

static char	*process_dollar(char *arg, int *i, t_env *env_list, int lst_ex_stats)
{
	char	*var_name;
	char	*var_value;
	char	*expanded;
	char	buf[2];

	if (arg[*i] != '$')
	{
		buf[0] = arg[*i];
		buf[1] = '\0';
		(*i)++;
		return(ft_strdup(buf));
	}
	(*i)++;
	var_name = extract_var_name(arg, i);
	if (!var_name)
		return (ft_strdup(""));
	var_value = exp_single_var(var_name, env_list, lst_ex_stats);
	free(var_name);
	expanded = ft_strdup(var_value);
	free(var_value);
	return(expanded);
}

char	*expand_arg(char *arg, t_env *env_list, int lst_exit_stats)
{
	char	*res;
	char	*tmp;
	int		i;
	int		in_single;
	int		in_double;

	if (!arg)
		return (NULL);
	res = NULL;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (arg[i])
	{
		update_quotes(arg[i], &in_single, &in_double);
		tmp = process_dollar(arg, &i, env_list, lst_exit_stats);
		res = append_to_res(res, tmp);
		free(tmp);
	}
	if (!res)
		res = ft_strdup("");
	return (res);
}

void	expand_args(t_input *node)
{
	int		i;
	char	*expanded;
	char	*original;

	if (!node || !node->argv)
		return;

	i = 0;
	while (node->argv[i])
	{
		original = node->argv[i];
		expanded = expand_arg(original, msh()->env, msh()->last_exit_status);
		if (expanded)
		{
			node->argv[i] = expanded;
			free(original);
		}
		i++;
	}
}

void	expand_all(t_msh *msh_data)
{
	t_list	*current;
	t_input	*node;

	current = msh_data->inputlst;
	while (current)
	{
		node = (t_input *)current->content;
		expand_args(node);
		current = current->next;
	}
}
