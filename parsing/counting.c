/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:16 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:17 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

static int	check_quote_change(char *s, int *i, int *in_s, int *in_d)
{
	if ((s[*i] == '\'' && !(*in_d)) || (s[*i] == '\"' && !(*in_s)))
	{
		update_quotes(s[*i], in_s, in_d);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_dquote_escape(char *s, int *i, int in_d)
{
	if (in_d && s[*i] == '\\' && s[*i + 1]
		&& (s[*i + 1] == '\"' || s[*i + 1] == '\\'
			|| s[*i + 1] == '$' || s[*i + 1] == '`'))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

void	arg_len(char *s, int *i, int *len)
{
	int	in_s;
	int	in_d;

	in_s = 0;
	in_d = 0;
	while (s[*i] && (in_s || in_d || s[*i] != ' '))
	{
		if (check_quote_change(s, i, &in_s, &in_d))
			*len += 1;
		else if (handle_dquote_escape(s, i, in_d))
			*len += 1;
		else
		{
			*len += 1;
			*i += 1;
		}
	}
}
