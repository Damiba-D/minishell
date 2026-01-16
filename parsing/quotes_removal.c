/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:49 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:50 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_quotes_str(char *str, int *in_sgl, int *in_dbl)
{
	int		i;
	int		j;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	*in_sgl = 0;
	*in_dbl = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !(*in_dbl)) || (str[i] == '\"' && !(*in_sgl)))
		{
			update_quotes(str[i], in_sgl, in_dbl);
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

static void	update_str(char **str, int *in_sgl, int *in_dbl)
{
	char	*tmp;

	if (!str || !(*str))
		return ;
	tmp = remove_quotes_str(*str, in_sgl, in_dbl);
	if (tmp)
	{
		free(*str);
		*str = tmp;
	}
}

void	remove_quotes_input(t_input *node)
{
	int		i;
	int		in_sgl;
	int		in_dbl;

	if (!node)
		return ;
	in_sgl = 0;
	in_dbl = 0;
	i = -1;
	while (node->argv && node->argv[++i])
		update_str(&node->argv[i], &in_sgl, &in_dbl);
	i = 0;
	while (node->infiles && node->infiles[i].filename)
		update_str(&node->infiles[i++].filename, &in_sgl, &in_dbl);
	i = 0;
	while (node->outfiles && node->outfiles[i].filename)
		update_str(&node->outfiles[i++].filename, &in_sgl, &in_dbl);
}
