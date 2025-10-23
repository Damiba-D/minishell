#include "../minishellM.h"

char	*remove_all_reds(char *seg)
{
	char	*cleaned;
	int		src_i;
	int		dst_i;
	int		red_pos;

	src_i = 0;
	dst_i = 0;
	cleaned = malloc(ft_strlen(seg) + 1);
	if (!cleaned)
		return (NULL);
	while (seg[src_i])
	{
		red_pos = find_next_red(seg, src_i);
		if (red_pos != -1)
		{
			cleaned[dst_i++] = seg[src_i++];
			src_i = skip_reds_filename(seg, src_i);
		}
		else
			cleaned[dst_i++] = seg[src_i++];
	}
	cleaned[dst_i] = '\0';
	return (cleaned);
}