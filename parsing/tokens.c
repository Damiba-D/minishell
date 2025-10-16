#include "../minishellM.h"

t_token *create_token(char *value, t_tokent type)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_back(t_token **list, t_token *new_token)
{
	t_token	*last;

	if (!list || !new_token)
		return ;
	if (!*list)
	{
		*list = new_token;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_token;
}

t_tokent identify_token_type(char *str, int pos)
{
	if (str[pos] == '|')
		return (PIPE);
	else if (str[pos] == '<' && str[pos + 1] == '<')
		return (HDOC);
	else if (str[pos] == '<')
		return (REDIN);
	else if (str[pos] == '>' && str[pos + 1] == '>')
		return (APPEND);
	else if (str[pos] == '>')
		return (REDOUT);
	else
		return (WORD);
}

t_token	*tokenizer(char *line, t_tokent type)
{
	t_token *token_list;
	t_token *current_token;
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		i = skip_whitespace(line, i);
		if (line[i] == '|')
		{
			current_token = create_token("|", PIPE);
			add_token_back(&token_list, current_token);
			i++;
		}
		else if (line[i] == '<')
		{
			current_token = create_token("<", REDOUT);
			add_token_back(&token_list, current_token);
			i++;
		}
	}
	return (token_list);
}
