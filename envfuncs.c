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
		if (!strncmp(key, env_list->key, ft_strlen(key)))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_env_value(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (!strncmp(key, env_list->key, ft_strlen(key)))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

void	set_env_value(const char *key, const char *value, t_env **env_list)
{
	t_env *temp;

	temp = *env_list;
	while (temp)
	{
		if (!strncmp(key, temp->key, ft_strlen(key)))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	env_add(env_list, env_new_node(ft_strdup(key), ft_strdup(value)));
}
