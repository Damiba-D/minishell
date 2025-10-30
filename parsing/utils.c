#include "../minishellM.h"

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

/* int ft_iscontrol(char c)
{
	return ((c == '&')
		|| (c == '(')
		|| (c == ')')
		|| (c == ';')
		|| (c == '<')
		|| (c == '>')
		|| (c == '\\')
		|| (c == '|'));
}

static int  get_size_token(char const *line)
{
	int	i;
	int	inside_quotes;
	
	i = 0;
	inside_quotes = 0;
	while (line[i]
		&& (inside_quotes || (!ft_isspace(line[i]) && !ft_iscontrol(line[i]))))
	{
		if ((!inside_quotes) && (line[i] == '\'' || line[i] == '\"'))
			inside_quotes = line[i];
		else if (inside_quotes == line[i])
			inside_quotes = 0;
		i++;
	}
	if (inside_quotes)
		return (-1);
	return (0);
} */