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
