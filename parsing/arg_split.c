#include "arg_split.h"

/* Check if quotes are balanced (bash rejects unmatched single quotes) */
static int	has_unmatched_quote(char *s)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (s[i])
	{
		if (!in_quote && s[i] == '\\' && s[i + 1])
		{
			i += 2;
			continue ;
		}
		if (s[i] == '\'' || s[i] == '\"')
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
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
		return (NULL);
	arr[i] = NULL;
	return (arr);
}
