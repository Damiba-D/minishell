#include "../minishellM.h"

char	*ext_reds_file(char *seg, t_tokent type)
{
	int	i;
	int	start_file;

	i = 0;
	while (seg[i])
	{
		if ((type == REDIN && seg[i] == '<' && seg[i + 1] != '<') ||
			(type == REDOUT && seg[i] == '>' && seg[i + 1] != '>'))
		{
			i++;
			break;
		}
		else if ((type == APPEND && seg[i] == '>' && seg[i + 1] == '>') ||
			(type == HDOC && seg[i] == '<' && seg[i + 1] == '<'))
		{
			i += 2;
			break;
		}
		i++;
	}
	i = skip_whitespace(seg, i);
	start_file = i;
	return (ext_reds_file_util(seg, start_file));
}

char	*ext_reds_file_util(char *seg, int start_pos)
{
	int	i;
	int	in_double;
	int	in_single;

	i = start_pos;
	in_double = 0;
	in_single = 0;
	while (seg[i] && (in_single || in_double || seg[i] != ' '))
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (ft_substr(seg, start_pos, i - start_pos));
}
