#include "minishellM.h"

int	skip_whitespace(char *str, int pos)
{
	while (str[pos] && ft_isspace(str[pos]))
		pos++;
	return (pos);
}
