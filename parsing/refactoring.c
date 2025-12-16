#include "../minishell.h"

char	**append_arrays(char **dst, char **src)
{
	int		dst_len;
	int		src_len;
	char	**res;
	int		i;
	int		j;

	dst_len = 0;
	while (dst && dst[dst_len])
		dst_len++;
	src_len = 0;
	while (src && src[src_len])
		src_len++;
	res = malloc(sizeof(char *) * (dst_len + src_len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < dst_len)
		res[i] = dst[i];
	j = -1;
	while (++j < src_len)
		res[i + j] = src[j];
	res[dst_len + src_len] = NULL;
	free(dst);
	return (res);
}

char	**resplit_after_expansion(char **argv)
{
	char	**res;
	char	**split;
	int		i;

	res = NULL;
	i = -1;
	while (argv && argv[++i])
	{
		split = arg_split(argv[i]);
		if (!split)
		{
			free_arr(res);
			return (NULL);
		}
		res = append_arrays(res, split);
		free(split);
		if (!res)
			return (NULL);
	}
	if (!res)
		res = calloc(1, sizeof(char *));
	return (res);
}
