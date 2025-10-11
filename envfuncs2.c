#include "minishellD.h"

void	free_env_node(t_env *env_node)
{
	if (env_node->key != NULL)
		free(env_node->key);
	if (env_node->value != NULL)
		free(env_node->value);
	free(env_node);
}

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

	size = env_lstsize(env_list);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (env_arr == NULL)
		malloc_err_exit(env_list, "env_list_to_char");
	i = 0;
	while (env_list)
	{
		size = ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2;
		env_arr[i] = (char *)malloc(sizeof(char) * size);
		if (env_arr[i] == NULL)
		{
			free_arr(env_arr);
			malloc_err_exit(env_list, "env_list_to_char");
		}
		ft_strlcpy(env_arr[i], env_list->key, size);
		ft_strlcat(env_arr[i], "=", size);
		ft_strlcat(env_arr[i++], env_list->value, size);
		env_list = env_list->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
