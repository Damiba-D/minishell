#include "execution.h"

static void	set_shell_lvl(t_env **env_list)
{
	t_env	*shell_lvl;
	int		new_lvl;

	shell_lvl = get_env_node("SHLVL", *env_list);
	if (shell_lvl)
	{
		new_lvl = ft_atoi(shell_lvl->value) + 1;
		free(shell_lvl->value);
		shell_lvl->value = ft_itoa(new_lvl);
		if (!shell_lvl->value)
			malloc_err_exit(*env_list, "init_env");
	}
	else
	{
		shell_lvl = env_new_node(NULL, NULL);
		shell_lvl->key = ft_strdup("SHLVL");
		shell_lvl->value = ft_strdup("1");
		if (!shell_lvl->key || !shell_lvl->value)
			return (free_env_node(shell_lvl), malloc_err_exit(*env_list, "init_env"));
		env_add(env_list, shell_lvl);
	}
}

void	init_env(t_env **env_list)
{
	extern char	**environ;
	int			i;
	int			len;
	t_env		*new;
	char		buf[PATH_MAX];

	*env_list = NULL;
	i = 0;
	while (environ[i])
	{
		len = 0;
		while (environ[i][len] != '=')
			len++;
		new = env_new_node(NULL, NULL);
		if (!new)
			malloc_err_exit(*env_list, "init_env");
		new->key = ft_strndup(environ[i], len);
		new->value = ft_strdup(environ[i] + len + 1);
		if (!new->key || !new->value)
			return (free_env_node(new), malloc_err_exit(*env_list, "init_env"));
		env_add(env_list, new);
		i++;
	}
	set_env_value("PWD", getcwd(buf, sizeof(buf)), env_list, false);
	set_shell_lvl(env_list);
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
