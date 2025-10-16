#include "../minishellM.h"

/// @brief counts the amount of pipes in the line
/// @param line 
/// @return count
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
/// @brief 
/// @param line 
/// @return segments
static char	**split_pipe(char *line)
{
	char	**segments;
	int		p_count;
	int		i;
	int		j;
	int		start;
	int		in_quote;

	p_count = count_pipes(line);
	segments = malloc(sizeof(char *) * (p_count + 2));
	if (!segments)
		return(NULL);
	i = 0;
	j = 0;
	start = 0;
	in_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
			in_quote = !in_quote;
		else if (line[i] == '\"' && (i == 0 || line[i - 1] != '\\'))
			in_quote = !in_quote;
		if (line[i] == '|' && !in_quote)
		{
			segments[j] = ft_substr(line, start, i - start);
			if (!segments[j])
				return(free_arr(segments), NULL);
			j++;
			start = i + 1;
		}
		i++;
	}
	segments[j] = ft_substr(line, start, i - start);
	if (!segments[j])
		return (free_arr(segments), NULL);
	j++;
	segments[j] = NULL;
	return (segments);
}

/// @brief Creates a new input node from a command segment
/// @param segment Command string segment
/// @return New t_input node or NULL on failure
t_input	*create_input_node(char *segment)
{
	t_input	*new_node;
	char	*cleaned_segment;
	int		inv_arg;

	new_node = ft_calloc(1 ,sizeof(t_input));
	if (!new_node)
		return (NULL);
	cleaned_segment = 
	new_node->argv = arg_split(segment, &inv_arg);
	if (inv_arg == 2 || !new_node->argv)
	{
		free(new_node);
		return (NULL);
	}
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->hdoc = 0;
	new_node->next = NULL;
	return (new_node);
}

void	add_input_back(t_input **lst, t_input *new)
{
	t_input	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_input	*parse_line(char *line)
{
	char	**segments;
	t_input	*input_list;
	t_input	*new_node;
	int		i;

	if (!line || !*line)
		return (NULL);
	segments = split_pipe(line);
	if (!segments)
		return (NULL);
	input_list = NULL;
	i = 0;
	while (segments[i])
	{
		new_node = create_input_node(segments[i]);
		if (!new_node)
		{
			free_arr(segments);
			free_input_list(input_list);
			return (NULL);
		}
		add_input_back(&input_list, new_node);
		i++;
	}
	free_arr(segments);
	return (input_list);
}
