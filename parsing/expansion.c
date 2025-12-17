#include "../minishell.h"

static char	*strip_invalid_dollars(char *arg)
{
	int		i;
	int		k;
	char	*res;
	int		in_d;
	int		in_s;

	if (!arg || !(res = malloc(ft_strlen(arg) + 1)))
		return (NULL);
	i = 0;
	k = 0;
	in_s = 0;
	in_d = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && !in_s && !in_d && (arg[i + 1] == '\''
				|| arg[i + 1] == '\"' || arg[i + 1] == '\0'))
		{
			i++;
			continue ;
		}
		res[k++] = arg[i];
		update_quotes(arg[i++], &in_s, &in_d);
	}
	res[k] = '\0';
	return (res);
}

static char	*expand_arg(char *arg)
{
	char	*result;
	char	*new_result;
	char	*stripped;
	int		last_replaced_end;

	if (!arg)
		return (NULL);
	stripped = strip_invalid_dollars(arg);
	if (!stripped)
		return(NULL);
	result = ft_strdup(stripped);
	free(stripped);
	if (!result)
		return (NULL);
	last_replaced_end = 0;
	while (result)
	{
		new_result = replace_next_var(result, &last_replaced_end);
		if (new_result == result)
			break ;
		if (!new_result)
			return (ft_strdup(""));
		result = new_result;
	}
	return (result);
}

static void	expand_args(t_input *node)
{
	int		i;
	char	*expanded;
	char	**new_arg;

	if (!node || !node->argv)
		return ;
	i = -1;
	while (node->argv[++i])
	{
		expanded = expand_arg(node->argv[i]);
		if (!expanded)
			expanded = ft_strdup("");
		free(node->argv[i]);
		node->argv[i] = expanded;
	}
	new_arg = resplit_after_expansion(node->argv);
	if (new_arg)
	{
		free_arr(node->argv);
		node->argv = new_arg;
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
