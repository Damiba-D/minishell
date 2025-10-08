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

int	env_cmd(t_env *env_list)
{
	while(env_list != NULL)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
