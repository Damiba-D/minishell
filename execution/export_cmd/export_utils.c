#include "../execution.h"
#include "export_cmd.h"

int	env_keycmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_env_array(t_env **env)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j + 1])
		{
			if (env_keycmp(env[j]->key, env[j + 1]->key) > 0)
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

int	is_invalid_identifier(char *arg, int *ret_val)
{
	int	i;
	int	inval;

	i = 0;
	inval = 0;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		inval = 1;
	while (arg[i] && !inval)
	{
		if (arg[i] == '=' || (arg[i] == '+' && arg[i + 1] == '='))
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			inval = 1;
		i++;
	}
	if (inval)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*ret_val = 1;
	}
	return (inval);
}

t_env	**lst_to_arr(t_env *env_list)
{
	t_env **arr;
	int i;	

	arr = (t_env **)malloc((env_lstsize(env_list) + 1) * sizeof(t_env));
	if (arr == NULL)
		malloc_err_exit("lst_to_arr");
	i = 0;
	while (env_list != NULL)
	{
		arr[i++] = env_list;
		env_list = env_list->next;
	}
	arr[i] = NULL;
	return (arr);
}
