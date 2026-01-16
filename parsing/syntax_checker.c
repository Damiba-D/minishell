/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:51:00 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:51:01 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_redir_token(char *s, int *i)
{
	*i = skip_whitespace(s, *i + 1 + (s[*i + 1] == s[*i]));
	if (!s[*i] || s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
		return (1);
	return (0);
}

static int	check_pipe_token(char *s, int *i)
{
	*i = skip_whitespace(s, *i + 1);
	if (!s[*i] || s[*i] == '|')
		return (1);
	return (0);
}

static int	check_redir_syntax(char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (s[++i])
	{
		update_quotes(s[i], &sq, &dq);
		if (sq || dq)
			continue ;
		if (s[i] == '<' || s[i] == '>')
		{
			if (check_redir_token(s, &i))
				return (1);
		}
		else if (s[i] == '|')
		{
			if (check_pipe_token(s, &i))
				return (1);
		}
	}
	return (0);
}

int	check_syntax(char *line)
{
	if (!line || !line[0])
		return (0);
	if (has_unmatched_quote(line))
	{
		ft_putendl_fd("syntax error: unmatched quote", 2);
		return (1);
	}
	if (check_redir_syntax(line))
	{
		ft_putendl_fd("syntax error: unexpected token", 2);
		return (1);
	}
	return (0);
}
