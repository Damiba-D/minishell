#include "minishellD.h"

static int	env_keycmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	sort_env_array(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j + 1])
		{
			if (env_keycmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		export_cmd(char **args, t_env **env_list)
{
	char **sorted_list;
	//t_env *new;
	int i;

	if (!args[1])
	{
		sorted_list = env_list_to_char(*env_list);
		sort_env_array(sorted_list);
		i = -1;
		while (sorted_list[++i])
			printf("%s\n", sorted_list[i]);
		free_arr(sorted_list);
		return (0);
	}
	return (0);
}
