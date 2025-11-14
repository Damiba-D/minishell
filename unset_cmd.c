#include "minishellD.h"

void	unset_env(const char *key, t_env **env_list)
{
	t_env *prev;
	t_env *targ;
	t_env *foll;
	size_t key_len;

	prev = NULL;
	targ = *env_list;
	foll = targ->next;
	key_len = ft_strlen(key) + 1;
	while (targ)
	{
		if (!ft_strncmp(key, targ->key, key_len))
		{
			if (prev == NULL)
				*env_list = targ->next;
			else
				prev->next = foll;
			free_env_node(targ);
			return ;
		}
		prev = targ;
		targ = foll;
		foll = targ->next;
	}
}

int		unset_cmd(char **args, t_env **env_list)
{
	int i;

	i = 0;
	while (args[++i])
	{
		if (get_env_node(args[i], *env_list) == NULL)
			continue ;
		unset_env(args[i], env_list);
	}
	return (0);
}
