#include "../minishell.h"

static char	*expand_arg(char *arg)
{
	char	*result;
	char	*new_result;
	int		last_replaced_end;

	if (!arg)
		return (NULL);
	result = ft_strdup(arg);
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
	if (!result)
		result = ft_strdup("");
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
