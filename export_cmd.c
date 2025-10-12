#include "minishellD.h"

static int	env_keycmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] != '=' && s2[i] != '=') && (s1[i] == s2[i]))
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

static int	is_invalid_identifier(char *arg, int *ret_val)
{
	int	i;
	int	inval;

	i = 0;
	inval = 0;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		inval = 1;
	while (arg[i] && !inval)
	{
		if (arg[i] == '=')
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

void	print_sorted_env(t_env *env_list)
{
	char **sorted_list;
	int i;

	sorted_list = env_list_to_char(env_list);
	sort_env_array(sorted_list);
	i = -1;
	while (sorted_list[++i])
		printf("%s\n", sorted_list[i]);
	free_arr(sorted_list);
}

int		export_cmd(char **args, t_env **env_list)
{
	int i;
	int ret_val;
	char *eq_pos;
	char *key;
	char *value;

	ret_val = 0;
	if (!args[1])
		print_sorted_env(*env_list);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (is_invalid_identifier(args[i], &ret_val))
				continue ;
			eq_pos = ft_strchr(args[i], '=');
			if (!eq_pos && !get_env_node(args[i], *env_list))
				set_env_value(args[i], NULL, env_list);
			if (eq_pos)
			{
				*eq_pos = '\0';
    			key = args[i];
    			value = eq_pos + 1;
    			set_env_value(key, value, env_list);
    			*eq_pos = '=';
			}
		}
	}
	return (ret_val);
}
