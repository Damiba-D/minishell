#include "arg_split.h"

/* Check if quotes are balanced (bash rejects unmatched single quotes) */
static int	has_unmatched_quote(char *s)
{
	int	i;
	int	in_quote;
	int in_dquote;

	i = 0;
	in_quote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if ((!in_quote || !in_dquote) && s[i] == '\\' && s[i + 1])
		{
			i += 2;
			continue ;
		}
		if (s[i] == '\'')
			in_quote = !in_quote;
		if (s[i] == '\"')
			in_dquote = !in_dquote;
		i++;
	}
	return (in_quote || in_dquote);
}

char	**arg_split(char *s, int *inv_arg)
{
	char	**arr;
	int		i;

	*inv_arg = 1;
	if (s == NULL)
		return (NULL);
	if (has_unmatched_quote(s))
	{
		*inv_arg = 2;
		return (NULL);
	}
	arr = (char **)malloc(((count_args(s) + 1) * sizeof(char *)));
	if (!arr)
		return (NULL);
	i = ft_cpy_alloc(arr, s);
	if (i == -1)
	{
		free(arr);
		return (NULL);
	}
	*inv_arg = 0;
	arr[i] = NULL;
	return (arr);
}
