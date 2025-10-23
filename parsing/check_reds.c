#include "../minishellM.h"

int	find_in_red(char *seg, int start_pos)
{
	int	i;
	int	in_double;
	int	in_single;
	int	last_pos;

	i = start_pos;
	in_single = 0;
	in_double = 0;
	last_pos = -1;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '<' && seg[i + 1] != '<')
				last_pos = i;
		}
		i++;
	}
	return (last_pos);
}

int	find_out_red(char *seg, int start_pos)
{
	int	i;
	int	in_double;
	int	in_single;
	int	last_pos;

	i = start_pos;
	in_single = 0;
	in_double = 0;
	last_pos = -1;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '>' && seg[i + 1] != '>')
				last_pos = i;
		}
		i++;
	}
	return (last_pos);
}

int	find_hdoc(char *seg, int start_pos)
{
	int	i;
	int	in_double;
	int	in_single;
	int	last_pos;

	i = start_pos;
	in_single = 0;
	in_double = 0;
	last_pos = -1;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '<' && seg[i + 1] == '<')
				last_pos = i;
		}
		i++;
	}
	return (last_pos);
}

int	find_append(char *seg, int start_pos)
{
	int	i;
	int	in_double;
	int	in_single;
	int	last_pos;

	i = start_pos;
	in_single = 0;
	in_double = 0;
	last_pos = -1;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '>' && seg[i + 1] == '>')
				last_pos = i;
		}
		i++;
	}
	return (last_pos);
}

int	find_next_red(char *seg, int start_pos)
{
	int hdoc_pos = find_hdoc(seg, start_pos);
	int append_pos = find_append(seg, start_pos);
	int in_pos = find_in_red(seg, start_pos);
	int out_pos = find_out_red(seg, start_pos);

	int	earliest;
	earliest = -1;
	if (hdoc_pos != -1 && (earliest == -1 || hdoc_pos < earliest))
		earliest = hdoc_pos;
	if (append_pos != -1 && (earliest == -1 || append_pos < earliest))
		earliest = append_pos;
	if (in_pos != -1 && (earliest == -1 || in_pos < earliest))
		earliest = in_pos;
	if (out_pos != -1 && (earliest == -1 || out_pos < earliest))
		earliest = out_pos;
	return (earliest);
}
