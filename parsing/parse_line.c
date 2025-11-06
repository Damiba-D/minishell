#include "../minishellM.h"

/// @brief counts the amount of pipes in the line
/// @param line 
/// @return count
static int	count_pipes(char *line)
{
	int	i;
	int	count;
	int	in_quote;
	int	in_dquote;

	i = 0;
	count = 0;
	in_quote = 0;
	in_dquote = 0;
	while (line[i])
	{
		update_quotes(line[i], &in_quote, &in_dquote);
		if (line[i] == '|' && !in_quote && !in_dquote)
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
	int		in_dquote;

	p_count = count_pipes(line);
	segments = malloc(sizeof(char *) * (p_count + 2));
	if (!segments)
		return(NULL);
	i = 0;
	j = 0;
	start = 0;
	in_quote = 0;
	in_dquote = 0;
	while (line[i])
	{
		update_quotes(line[i], &in_quote, &in_dquote);
		if (line[i] == '|' && !in_quote && !in_dquote)
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
	char	*cleaned_seg;
	int		inv_arg;
	char	**append_files;

	new_node = ft_calloc(1 ,sizeof(t_input));
	if (!new_node)
		return (NULL);
	if (find_next_red(segment, 0, HDOC) != -1)
		new_node->hdoc = ext_reds_file(segment, HDOC);
	if (find_next_red(segment, 0, REDIN) != -1)
		new_node->infile = ext_reds_file(segment, REDIN);
	if (find_next_red(segment, 0, REDOUT) != -1)
		new_node->outfile = ext_reds_file(segment, REDOUT);
	if (find_next_red(segment, 0, APPEND) != -1)
	{
		append_files = ext_reds_file(segment, APPEND);
		if (append_files)
		{
			if (!new_node->outfile)
				new_node->outfile = append_files;
			else
				free_arr(append_files);
			new_node->append = 1;
		}
	}
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
			ft_lstclear(&input_list, free_input_node);
			return (NULL);
		}
		new = ft_lstnew(new_node);
		if (!new)
		{
			free_arr(segments);
			ft_lstclear(&input_list, free_input_node);
			return (NULL);
		}
		ft_lstadd_back(&input_list, new);
		i++;
	}
	free_arr(segments);
	return (input_list);
}
