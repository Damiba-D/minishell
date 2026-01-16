/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:46:33 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:46:34 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "export_cmd.h"

static void	export_non_null(char *eq_pos, char *pl_pos, char *arg, \
t_env **env_list)
{
	char	*key;
	char	*value;

	if (!pl_pos)
	{
		*eq_pos = '\0';
		key = arg;
		value = eq_pos + 1;
		set_env_value(key, value, env_list, false);
		*eq_pos = '=';
	}
	else
	{
		*pl_pos = '\0';
		key = arg;
		value = eq_pos + 1;
		set_env_value(key, value, env_list, true);
		*pl_pos = '+';
	}
}

static void	print_sorted_env(t_env *env_list)
{
	t_env	**sorted_list;
	int		i;

	sorted_list = lst_to_arr(env_list);
	sort_env_array(sorted_list);
	i = -1;
	while (sorted_list[++i])
	{
		if (!(sorted_list[i]->key[0] == '_' && !sorted_list[i]->key[1]))
		{
			printf("declare -x %s", sorted_list[i]->key);
			if (sorted_list[i]->value != NULL)
				printf("=\"%s\"", sorted_list[i]->value);
			printf("\n");
		}
	}
	free(sorted_list);
}

int	export_cmd(char **args)
{
	int		i;
	int		ret_val;
	char	*eq_pos;
	char	*pl_pos;

	ret_val = 0;
	if (!args[1])
		print_sorted_env(msh()->env);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (is_invalid_identifier(args[i], &ret_val))
				continue ;
			eq_pos = ft_strchr(args[i], '=');
			pl_pos = ft_strchr(args[i], '+');
			if (!eq_pos && !get_env_node(args[i], msh()->env))
				set_env_value(args[i], NULL, &msh()->env, false);
			if (eq_pos)
				export_non_null(eq_pos, pl_pos, args[i], &msh()->env);
		}
	}
	return (ret_val);
}
