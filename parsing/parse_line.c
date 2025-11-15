#include "parsing.h"

static char	*extract_segment(char *line, int *pos)
{
	int	start;
	int	in_quote;
	int	in_dquote;

	start = *pos;
	in_quote = 0;
	in_dquote = 0;
	while (line[*pos])
	{
		update_quotes(line[*pos], &in_quote, &in_dquote);
		if (line[*pos] == '|' && !in_quote && !in_dquote)
			break ;
		(*pos)++;
	}
	return (ft_substr(line, start, *pos - start));
}

/// @brief 
/// @param line 
/// @return segments
static char	**split_pipe(char *line)
{
	char	**segments;
	int		pos;
	int		j;

	segments = malloc(sizeof(char *) * (count_pipes(line) + 2));
	if (!segments)
		return (NULL);
	pos = 0;
	j = 0;
	while (line[pos])
	{
		segments[j] = extract_segment(line, &pos);
		if (!segments[j])
			return (free_arr(segments), NULL);
		j++;
		if (line[pos] == '|')
			pos++;
	}
	segments[j] = NULL;
	return (segments);
}

/// @brief Creates a new input node from a command segment
/// @param segment Command string segment
/// @return New t_input node or NULL on failure
t_input	*create_input_node(char *segment)
{
	t_input	*new_node;
	char	*cleaned_seg;
	int		inv_arg;

	new_node = ft_calloc(1, sizeof(t_input));
	if (!new_node)
		return (NULL);
	ext_reds_file(segment, new_node);
	cleaned_seg = remove_all_reds(segment);
	new_node->argv = arg_split(cleaned_seg, &inv_arg);
	free(cleaned_seg);
	if (inv_arg == 2 || !new_node->argv)
		return (free_input_node(new_node), NULL);
	return (new_node);
}

t_list	*parse_line(char *line)
{
	char	**segments;
	t_list	*input_list;
	t_list	*new;
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
		new = ft_lstnew(NULL);
		if (!new)
			return (free_all(segments, &input_list, NULL), NULL);
		new->content = create_input_node(segments[i]);
		if (!new->content)
			return (free_all(segments, &input_list, new->content), NULL);
		ft_lstadd_back(&input_list, new);
		i++;
	}
	return (free_arr(segments), input_list);
}
