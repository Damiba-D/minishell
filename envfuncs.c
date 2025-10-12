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

void	set_env_value(const char *key, const char *value, t_env **env_list)
{
	t_env *temp;

	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, (ft_strlen(key) + 1)))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (temp->value == NULL)
				malloc_err_exit(*env_list, "set_env_value");
			return ;
		}
		temp = temp->next;
	}
	temp = env_new_node(NULL, NULL);
	if (temp == NULL)
		malloc_err_exit(*env_list, "set_env_value");
	temp->key = ft_strdup(key);
	if (temp->key == NULL)
		return (free_env_node(temp), malloc_err_exit(*env_list, "set_env_value"));
	temp->value = ft_strdup(value);
	if (temp->value == NULL)
		return (free_env_node(temp), malloc_err_exit(*env_list, "set_env_value"));
	env_add(env_list, temp);
}
