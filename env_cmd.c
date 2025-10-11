#include "minishellD.h"

void init_env(t_env **env_list)
{
	extern char	**environ;
	int			i;
	int			len;
	t_env		*new;

	*env_list = NULL;
	i = 0;
	while (environ[i])
	{
		len = 0;
		while (environ[i][len] && environ[i][len] != '=')
			len++;
		new = env_new_node(ft_strndup(environ[i], len + 1), ft_strdup(environ[i] + len + 1));
		if (new == NULL || new->key == NULL || new->value == NULL)
			malloc_err_exit(*env_list, "init_env");
		env_add(env_list, new);
		i++;
	}
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
