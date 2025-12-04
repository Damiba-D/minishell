#include "arg_split.h"

// Handles backslash escapes outside of quotes
static int	back_sl_out_quote(char *s, int *i, int in_s, int in_d)
{
	if (!in_s && !in_d && s[*i] == '\\' && s[*i + 1])
	{
		*i += 2;
		return (1);
	}
	return (0);
}

// Handles backslash escapes inside double quotes
static int	handle_dquote_escape(char *s, int *i, int *len)
{
	if (s[*i] == '\\' && s[*i + 1]
		&& (s[*i + 1] == '\"' || s[*i + 1] == '\\'
			|| s[*i + 1] == '$' || s[*i + 1] == '`'))
	{
		*len += 2;
		*i += 2;
		return (1);
	}
	return (0);
}

// Checks if current char is a quote and toggles quote
static int	check_quote_change(char *s, int *i, int *in_s, int *in_d)
{
	int	prev_i;

	prev_i = *i;
	if (s[*i] == '\'' && !(*in_d))
	{
		*in_s = !(*in_s);
		(*i)++;
	}
	else if (s[*i] == '\"' && !(*in_s))
	{
		*in_d = !(*in_d);
		(*i)++;
	}
	return (*i != prev_i);
}

static void	process_char(char *s, int *i, int *len, int in_d)
{
	if (in_d && handle_dquote_escape(s, i, len))
		return ;
	*len += 1;
	*i += 1;
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
		{
			*len += 1;
			continue ;
		}
		if (handle_escape_outside(s, i, in_s, in_d))
		{
			*len += 1;
			continue ;
		}
		process_char(s, i, len, in_d);
	}
}
