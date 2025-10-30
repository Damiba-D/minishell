#include "../minishellM.h"

char	*remove_all_reds(char *seg)
{
	char	*cleaned;
	int		src_i;
	int		dst_i;
	int		in_single;
	int		in_double;

	src_i = 0;
	dst_i = 0;
	in_single = 0;
	in_double = 0;
	cleaned = malloc(ft_strlen(seg) + 1);
	if (!cleaned)
		return (NULL);
	while (seg[src_i])
	{
		update_quotes(seg[src_i], &in_single, &in_double);
		if (!in_single && !in_double && 
			((seg[src_i] == '<') || (seg[src_i] == '>')))
			src_i = skip_reds_filename(seg, src_i);
		else
			cleaned[dst_i++] = seg[src_i++];
	}
	cleaned[dst_i] = '\0';
	return (cleaned);
}
