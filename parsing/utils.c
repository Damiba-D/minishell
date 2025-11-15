#include "parsing.h"

int	skip_whitespace(char *str, int pos)
{
	while (str[pos] && ft_isspace(str[pos]))
		pos++;
	return (pos);
}

void	update_quotes(char c, int *in_quote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_quote = !(*in_quote);
	else if (c == '\"' && !(*in_quote))
		*in_dquote = !(*in_dquote);
}

int	skip_reds_filename(char *seg, int start_pos)
{
	int	i;
	int	in_quote;
	int	in_dquote;

	i = start_pos;
	in_quote = 0;
	in_dquote = 0;
	if (seg[i] == '<' && seg[i + 1] == '<')
		i += 2;
	else if (seg[i] == '>' && seg[i + 1] == '>')
		i += 2;
	else if (seg[i] == '<' || seg[i] == '>')
		i += 1;
	else
		return (i);
	i = skip_whitespace(seg, i);
	while (seg[i] && ((in_quote || in_dquote) || seg[i] != ' '))
	{
		update_quotes(seg[i], &in_quote, &in_dquote);
		i++;
	}
	return (i);
}

/// @brief counts the amount of pipes in the line
/// @param line 
/// @return count
int	count_pipes(char *line)
{
	int	i;
	int	count;
	int	in_quote;
	int	in_dquote;

	i = 0;
	count = 0;
	in_quote = 0;
	in_dquote = 0;
	while (line[i])
	{
		update_quotes(line[i], &in_quote, &in_dquote);
		if (line[i] == '|' && !in_quote && !in_dquote)
			count++;
		i++;
	}
	return (count);
}
