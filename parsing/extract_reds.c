/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_reds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:34 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:35 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ext_reds_file_single(char *seg, int *i, t_input *node, int *red_i)
{
	int	type;

	if (seg[*i] == '<')
		type = REDIN;
	else
		type = REDOUT;
	if (seg[*i + 1] == seg[*i])
	{
		(*i)++;
		type += 2;
	}
	*i = skip_whitespace(seg, *i + 1);
	if (!seg[*i])
		return ;
	if (type == REDIN || type == HDOC)
		node->infiles[*red_i].mode = type;
	else
		node->outfiles[*red_i].mode = type;
	if (type == REDIN || type == HDOC)
		node->infiles[*red_i].filename
			= ext_reds_file_util(seg, i, &node->infiles[*red_i].quoted);
	else
		node->outfiles[*red_i].filename
			= ext_reds_file_util(seg, i, &node->outfiles[*red_i].quoted);
	(*red_i)++;
}

static int	allocate_file_arrays(t_input *node, int in_count, int out_count)
{
	node->infiles = ft_calloc(in_count + 1, sizeof(t_file));
	node->outfiles = ft_calloc(out_count + 1, sizeof(t_file));
	if (!node->infiles || !node->outfiles)
	{
		free(node->infiles);
		free(node->outfiles);
		return (0);
	}
	return (1);
}

void	ext_reds_file(char *seg, t_input *node)
{
	int	in_i;
	int	out_i;
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	count_reds(seg, &in_i, &out_i);
	if (!allocate_file_arrays(node, in_i, out_i))
		return ;
	in_i = 0;
	out_i = 0;
	while (seg[i])
	{
		update_quotes(seg[i], &squote, &dquote);
		if (!squote && !dquote && seg[i] == '<')
			ext_reds_file_single(seg, &i, node, &in_i);
		else if (!squote && !dquote && seg[i] == '>')
			ext_reds_file_single(seg, &i, node, &out_i);
		else
			i++;
	}
}

char	*ext_reds_file_util(char *seg, int *i, bool *quoted)
{
	int		k;
	int		in_quote;
	int		in_dquote;
	char	*res;

	k = 0;
	in_quote = 0;
	in_dquote = 0;
	*quoted = false;
	res = malloc(ft_strlen(seg + *i) + 1);
	if (!res)
		return (NULL);
	while (seg[*i] && ((in_quote || in_dquote) || seg[*i] != ' '))
	{
		update_quotes(seg[*i], &in_quote, &in_dquote);
		if (in_quote || in_dquote)
			*quoted = true;
		res[k++] = seg[*i];
		(*i)++;
	}
	res[k] = '\0';
	return (res);
}
