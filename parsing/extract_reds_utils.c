#include "../minishell.h"

static void	process_redir(char *seg, int *i, int *in, int *out)
{
	char	type;

	type = seg[*i];
	if (seg[*i + 1] == seg[*i])
		(*i)++;
	*i = skip_whitespace(seg, *i + 1);
	if (seg[*i])
	{
		if (type == '<')
			(*in)++;
		else
			(*out)++;
	}
}

int	count_reds(char *seg, int *in, int *out)
{
	int	i;
	int	sq;
	int	dq;

	*in = 0;
	*out = 0;
	i = 0;
	sq = 0;
	dq = 0;
	while (seg[i])
	{
		update_quotes(seg[i], &sq, &dq);
		if (!sq && !dq && (seg[i] == '<' || seg[i] == '>'))
		{
			process_redir(seg, &i, in, out);
			if (!seg[i])
				return (1);
		}
		else
			i++;
	}
	return (0);
}
