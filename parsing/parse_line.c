#include "minishellM.h"

static int	count_pipes(char *line)
{
	int	i;
	int	count;
	int	in_quote;

	i = 0;
	count = 0;
	in_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
			in_quote = !in_quote;
		if (line[i] == '|' && !in_quote)
			count++;
		i++;
	}
	return(count);
}

t_input	*parse_line(char *line)
{
	
}