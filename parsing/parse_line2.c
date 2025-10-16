#include "minishellM.h"

int	find_next_op(char *line, int start, char *op_found)
{
	int	i;
	int	in_quote;

	in_quote = 0;
	i = start;
	while (line[i])
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
			in_quote = !in_quote;
		if (!in_quote)
		{
			if (line[i] == '|')
			{
				*op_found = '|';
				return (i);
			}
			else if (line[i] == '<' && line[i + 1] == '<')
			{
				strcpy(op_found, "<<");
				return (i);
			}
			else if (line[i] == '<')
			{
				*op_found = '<';
				return (i);
			}
			else if (line[i] == '>')
			{
				*op_found = '>';
				return (i);
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				*op_found = '>>';
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

char	*parse_red(t_input *node, char *segments)
{

}
