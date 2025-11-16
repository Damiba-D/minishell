#include "../minishell.h"

int	env_lstsize(t_env *lst)
{
	int		count;
	t_env	*temp;

	if (lst == NULL)
		return (0);
	temp = lst;
	count = 1;
	while (temp->next != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char **env_list_to_char(t_env *env_list)
{
	int		size;
	char	**env_arr;
	int		i;

	env_arr = (char **)malloc(sizeof(char *) * (env_lstsize(env_list) + 1));
	if (env_arr == NULL)
		malloc_err_exit("env_list_to_char");
	i = 0;
	while (env_list)
	{
		size = ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2;
		env_arr[i] = (char *)malloc(sizeof(char) * size);
		if (env_arr[i] == NULL)
			return (free_arr(env_arr), malloc_err_exit("env_list_to_char"), NULL);
		ft_strlcpy(env_arr[i], env_list->key, size);
		if (env_list->value != NULL)
		{
			ft_strlcat(env_arr[i], "=", size);
			ft_strlcat(env_arr[i], env_list->value, size);
		}
		i++;
		env_list = env_list->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

static void update_env_value(t_env *node, const char *value, bool append)
{
	char *temp;

	if (!append)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (node->value == NULL)
			malloc_err_exit("set_env_value");
	}
	else if (append)
	{
		temp = node->value;
		if (node->value != NULL)
			node->value = ft_strjoin(node->value, value);
		else
			node->value = ft_strdup(value);
		free(temp);
		if (node->value == NULL)
			malloc_err_exit("set_env_value");
	}
}

void	set_env_value(const char *key, const char *value, t_env **env_list, bool append)
{
	t_env *temp;
	char *n_key;
	char *n_value;

	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, (ft_strlen(key) + 1)))
			return (update_env_value(temp, value, append));
		temp = temp->next;
	}
	n_key = ft_strdup(key);
	n_value = ft_strdup(value);
	if ((n_key == NULL ) || (n_value == NULL && value != NULL))
		return (free(n_key), free(n_value), malloc_err_exit("set_env_value"));
	temp = env_new_node(n_key, n_value);
	if (temp == NULL)
		return (free(n_key), free(n_value), malloc_err_exit("set_env_value"));
	env_add(env_list, temp);
}


/*
	char *temp
	char *temp2
	temp = strjoin(key, =)
	temp2 = strjoin(temp, value)
*/