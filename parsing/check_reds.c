#include "../minishellM.h"

int	has_in_red(char *seg)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_out_red(char *seg)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_hdoc(char *seg)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '<' && seg[i + 1] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_append(char *seg)
{
	int	i;
	int	in_double;
	int	in_single;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (seg[i])
	{
		if (seg[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (seg[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (seg[i] == '>' && seg[i + 1] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_red(char *seg)
{
	if (has_hdoc(seg))
		return (HDOC);
	if (has_append(seg))
		return (APPEND);
	if (has_in_red(seg))
		return (REDIN);
	if (has_out_red(seg))
		return (REDOUT);
	return (0);
}