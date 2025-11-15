
#include "minishell.h"

void	debug_print_input_list(t_list *input_list)
{
	t_list	*current;
	int		i;
	int 	cmd_num = 0;
	t_input *input;

	current = input_list;
	printf("=== DEBUG: Parsed Commands ===\n");
	while (current)
	{
		input = (t_input *)current->content;
		printf("Command %d:\n", cmd_num++);
		if (input->argv)
		{
			i = 0;
			while (input->argv[i])
			{
				printf("  argv[%d]: %s\n", i, input->argv[i]);
				i++;
			}
		}
		else
			printf("  argv: NULL\n");
		if (input->infiles)
		{
			i = 0;
			while (input->infiles[i].filename)
			{
				printf("  infile[%d]: %s\n", i, input->infiles[i].filename);
				if (input->infiles[i].mode == REDIN)
					printf("  mode[%d]: infile\n", i);
				else if (input->infiles[i].mode == HDOC)
					printf("  mode[%d]: heredoc\n", i);
				i++;
			}
		}
		else
			printf("  infile: NULL\n");
		if (input->outfiles)
		{
			i = 0;
			while (input->outfiles[i].filename)
			{
				printf("  outfile[%d]: %s\n", i, input->outfiles[i].filename);
				if (input->outfiles[i].mode == REDOUT)
					printf("  mode[%d]: truncate\n", i);
				else if (input->outfiles[i].mode == APPEND)
					printf("  mode[%d]: append\n", i);
				i++;
			}
		}
		else
			printf("  outfile: NULL\n");
		printf("  next: %s\n", current->next ? "exists" : "NULL");
		printf("---\n");
		current = current->next;
	}
	printf("=== END DEBUG ===\n");
}

int	main(void)
{
	char	*input;
	t_list	*input_list;
	t_list	*current;
	t_input	*input_test;
	int		i;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			exit(0);
		if (!input[0])
		{
			free(input);
			continue ;
		}
		add_history(input);
		input_list = parse_line(input);
		if (!input_list)
		{
			printf("syntax error: unmatched quote\n");
			free(input);
			continue ;
		}
		debug_print_input_list(input_list);
		input_test = (t_input *)input_list->content;
		if (input_test->argv && input_test->argv[0]
			&& (!strncmp(input_test->argv[0], "exit", 4)
				&& input_test->argv[0][4] == '\0'))
		{
			ft_lstclear(&input_list, free_input_node);
			free(input);
			exit(0);
		}
		current = input_list;
		while (current)
		{
			input_test = (t_input *)current->content;
			if (input_test->argv && input_test->argv[0])
			{
				i = 0;
				while (input_test->argv[i])
				{
					printf("%s", input_test->argv[i]);
					if (input_test->argv[i + 1])
						printf(" ");
					i++;
				}
				if (current->next)
					printf(" | ");
			}
			current = current->next;
		}
		printf("\n");
		ft_lstclear(&input_list, free_input_node);
		free(input);
	}
	return (0);
}
