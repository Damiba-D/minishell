/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:47:39 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:47:40 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_env(const char *key, t_env **env_list)
{
	t_env	*prev;
	t_env	*targ;
	t_env	*foll;
	size_t	key_len;

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

int	unset_cmd(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (get_env_node(args[i], msh()->env) == NULL)
			continue ;
		unset_env(args[i], &msh()->env);
	}
	return (0);
}
