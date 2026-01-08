#include "../minishell.h"

static int	check_redir_syntax(char *s)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (s[i])
	{
		update_quotes(s[i], &squote, &dquote);
		if (!squote && !dquote && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
		{
			if (s[i + 1] == s[i] && s[i] != '|')
				i++;
			i = skip_whitespace(s, i + 1);
			if (!s[i] || s[i] == '|' || s[i] == '<' || s[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *line)
{
	if (!line || !line[0])
		return (0);
	if (has_unmatched_quote(line))
	{
		ft_putendl_fd("syntax error: unmatched quote", 2);
		return (1);
	}
	if (check_redir_syntax(line))
	{
		ft_putendl_fd("syntax error: unexpected token", 2);
		return (1);
	}
	return (0);
}