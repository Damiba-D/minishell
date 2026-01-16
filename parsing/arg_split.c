/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:07 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:08 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

/* Check if quotes are balanced (bash rejects unmatched single quotes) */
int	has_unmatched_quote(char *s)
{
	int	i;
	int	in_quote;
	int	in_dquote;

	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_quote = !in_quote;
		else if (s[i] == '\"' && !in_quote)
			in_dquote = !in_dquote;
		i++;
	}
	return (in_quote || in_dquote);
}

static int	count_args(char *s)
{
	int	count;
	int	i;
	int	in_quote;
	int	in_dquote;

	count = 0;
	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && (in_quote || in_dquote || s[i] != ' '))
		{
			update_quotes(s[i], &in_quote, &in_dquote);
			i++;
		}
	}
	return (count);
}

char	**arg_split(char *s)
{
	char	**arr;
	int		i;

	if (s == NULL)
		return (NULL);
	if (has_unmatched_quote(s))
		return (NULL);
	arr = (char **)malloc(((count_args(s) + 1) * sizeof(char *)));
	if (!arr)
		return (NULL);
	i = ft_cpy_alloc(arr, s);
	if (i == -1)
	{
		free(arr);
		return (NULL);
	}
	arr[i] = NULL;
	return (arr);
}
