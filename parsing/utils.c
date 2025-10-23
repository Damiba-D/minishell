#include "../minishellM.h"

int	skip_whitespace(char *str, int pos)
{
	while (str[pos] && ft_isspace(str[pos]))
		pos++;
	return (pos);
}

int	skip_reds_filename(char *seg, int start_pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = start_pos;
	if (seg[i] == '<' && seg[i + 1] == '<')
		i += 2;
	else if (seg[i] == '>' && seg[i + 1] == '>')
		i += 2;
	else if (seg[i] == '<' || seg[i] == '>')
		i += 1;
	else
		return (i);
	i = skip_whitespace(seg, i);
	in_single = 0;
	in_double = 0;
	while (seg[i] && (in_single || in_double || seg[i] != ' '))
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (i);
}
