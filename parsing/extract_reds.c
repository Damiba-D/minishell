#include "../minishellM.h"

int	find_next_red(char *seg, int start_pos, t_tokent type)
{
	int	i;
    int	in_single;
    int	in_double;

    i = start_pos;
    in_single = 0;
    in_double = 0;
	while (seg[i])
	{
		update_quotes(seg[i], &in_single, &in_double);
		if (!in_single && !in_double)
		{
			if (type == REDIN && seg[i] == '<' && seg[i + 1] != '<')
                return (i);
            else if (type == REDOUT && seg[i] == '>' && seg[i + 1] != '>')
                return (i);
            else if (type == APPEND && seg[i] == '>' && seg[i + 1] == '>')
                return (i);
            else if (type == HDOC && seg[i] == '<' && seg[i + 1] == '<')
                return (i);
		}
		i++;
	}
	return (-1);
}

static int	count_reds(char *seg, t_tokent type)
{
	int	count;
	int	start_pos;

	count = 0;
	start_pos = 0;
	while (1)
	{
		start_pos = find_next_red(seg, start_pos, type);
		if (start_pos == -1)
			break;
		count++;
		start_pos++;
	}
	return (count);
}

char	*ext_reds_file_single(char *seg, int red_pos, t_tokent type)
{
	int	start_file;

	if(red_pos == -1)
		return (NULL);
	if (type == APPEND || type == HDOC)
        red_pos += 2;
	else
        red_pos += 1;
	start_file = skip_whitespace(seg, red_pos);
	return (ext_reds_file_util(seg, start_file));
}

char	**ext_reds_file(char *seg, t_tokent type)
{
	char	**files;
	int		count;
	int		start_pos;
	int		i;

	count = count_reds(seg, type);
	if (count == 0)
		return (NULL);
	files = malloc(sizeof(char *) * (count + 1));
	if (!files)
		return (NULL);
	i = 0;
	start_pos = 0;
	while (i < count)
	{
		start_pos = find_next_red(seg, start_pos, type);
        files[i] = ext_reds_file_single(seg, start_pos, type);
		if (!files[i])
		{
			while(--i >= 0)	// temp: create return error or something
				free(files[i]);
			free(files);
			return (NULL);
		}
		i++;
		start_pos++;
	}
	files[i] = NULL;
	return (files);
}

char	*ext_reds_file_util(char *seg, int start_pos)
{
	int		i;
	int		k;
	int		in_quote;
	int		in_dquote;
	char	*res;

	res = malloc(ft_strlen(seg + start_pos) + 1);
	if (!res)
		return (NULL);
	i = start_pos;
	k = 0;
	in_quote = 0;
	in_dquote = 0;
	while (seg[i] && ((in_quote || in_dquote) || seg[i] != ' '))
	{
		update_quotes(seg[i], &in_quote, &in_dquote);
		if ((seg[i] != '\'' && seg[i] != '\"') || (i > 0 && seg[i - 1] == '\\'))
			res[k++] = seg[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}
