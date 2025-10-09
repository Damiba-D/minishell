#include "minishellD.h"

void	unset_env(const char *key, t_env **env_list)
{
	t_env *prev;
	t_env *targ;
	t_env *foll;

	prev = NULL;
	targ = *env_list;
	foll = targ->next;
	while (targ)
	{
		if (!strncmp(key, targ->key, ft_strlen(key)))
		{
			if (prev != NULL)
				prev->next = foll;
			free_env_node(targ);
			return ;
		}
		prev = targ;
		targ = foll;
		foll = targ->next;
	}
}

static int is_invalid_identifier(char *arg, int *ret_val)
{
	int i;
	int inval;

	i = 0;
	inval = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		inval = 1;
    while (arg[i] && !inval) 
	{
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
			inval = 1;
		i++;
    }
	if (inval && !(*ret_val))
	{
		*ret_val = 1;
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
	}
    return (inval);
}

int		unset_cmd(char **args, t_env **env_list)
{
	int i;
	int ret_val;

	ret_val = 0;
	i = 0;
	while (args[++i])
	{
		if (is_invalid_identifier(args[i], &ret_val))
			continue ;
		if (get_env_node(args[i], *env_list) == NULL)
			continue ;
		unset_env(args[i], env_list);
	}
	return (ret_val);
}
