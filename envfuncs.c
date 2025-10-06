#include "minishellD.h"

t_env	*env_new_node(char *key, char *value)
{
	t_env	*new;

	new->key = key;
	new->value = value;
	return (new);
}

void	env_add(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env *init_env(t_env *env_list)
{
	extern char	**environ;
	int			i;

	env_list = NULL;
	i = 0;
	while (environ[i])
	{
		
	}
}
