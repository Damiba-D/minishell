#include "minishellD.h"

void init_env(t_env **env_list)
{
	extern char	**environ;
	int			i;
	int			len;

	*env_list = NULL;
	i = 0;
	while (environ[i])
	{
		len = 0;
		while (environ[i][len] && environ[i][len] != '=')
			len++;
		env_add(env_list, env_new_node(ft_strndup(environ[i], len + 1), ft_strdup(environ[i] + len + 1)));
		i++;
	}
}
void	free_env_node(t_env *env_node)
{
	if (env_node->key != NULL)
		free(env_node->key);
	if (env_node->value != NULL)
		free(env_node->value);
	free(env_node);
}

void term_env(t_env *env_list)
{
	t_env *temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free_env_node(temp);
	}
}

int	env_cmd(t_env *env_list)
{
	while(env_list != NULL)
	{
		if (env_list->value != NULL)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
