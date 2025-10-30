#include "../minishellM.h"

char	*ext_reds_file(char *seg, t_tokent type)
{
	int	i;
	int	start_file;
	int	red_pos;

	i = 0;
	if (type == REDIN)
		red_pos = find_in_red(seg, 0);
	else if (type == REDOUT)
		red_pos = find_out_red(seg, 0);
	else if (type == APPEND)
		red_pos = find_append(seg, 0);
	else if (type == HDOC)
			red_pos = find_hdoc(seg, 0);
	else
		return (NULL);
	if (red_pos == -1)
		return (NULL);
	if (type == APPEND || type == HDOC)
		red_pos += 2;
	else
		red_pos += 1;
	i = skip_whitespace(seg, i);
	start_file = i;
	return (ext_reds_file_util(seg, start_file));
}

char	*ext_reds_file_util(char *seg, int start_pos)
{
	int		i;
	int		k;
	int		in_quote;
	int		in_word;
	char	*res;

	res = malloc(ft_strlen(seg + start_pos) + 1);
	if (!res)
		return (NULL);
	i = start_pos;
	k = 0;
	in_quote = 0;
	in_word = 0;
	while (seg[i] && (in_quote || seg[i] != ' '))
	{
		handle_quote(seg, i, &in_quote, &in_word);
		handle_dquote(seg, i, &in_quote, &in_word);
		if ((seg[i] != '\'' && seg[i] != '\"') || (i > 0 && seg[i - 1] == '\\'))
			res[k++] = seg[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}
