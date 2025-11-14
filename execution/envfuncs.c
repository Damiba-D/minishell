#include "minishellD.h"

t_env	*env_new_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
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

t_env *get_env_node(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(key, env_list->key, (ft_strlen(key) + 1)))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_env_value(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(key, env_list->key, (ft_strlen(key) + 1)))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

void	free_env_node(t_env *env_node)
{
	if (env_node->key != NULL)
		free(env_node->key);
	if (env_node->value != NULL)
		free(env_node->value);
	free(env_node);
}

