
#include "minishellM.h"

void	free_input_node(void *content)
{
	t_input *input;

	input = (t_input *)content;
	if (input->argv)
		free_arr(input->argv);
	if (input->infile)
		free_arr(input->infile);
	if (input->outfile)
		free_arr(input->outfile);
	if (input->hdoc)
		free_arr(input->hdoc);
	free(input);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	debug_print_input_list(t_list *input_list)
{
    t_list *current;
    int i;
    int cmd_num = 0;
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
        if (input->infile)
        {
            i = 0;
            while (input->infile[i])
            {
                printf("  infile[%d]: %s\n", i, input->infile[i]);
                i++;
            }
        }
        else
            printf("  infile: NULL\n");
        if (input->outfile)
        {
            i = 0;
            while (input->outfile[i])
            {
                printf("  outfile[%d]: %s\n", i, input->outfile[i]);
                i++;
            }
        }
        else
            printf("  outfile: NULL\n");
        printf("  append: %d\n", input->append);
        if (input->hdoc)
        {
            i = 0;
            while (input->hdoc[i])
            {
                printf("  hdoc[%d]: %s\n", i, input->hdoc[i]);
                i++;
            }
        }
        else
            printf("  hdoc: NULL\n");
        printf("  next: %s\n", current->next ? "exists" : "NULL");
        printf("---\n");
        current = current->next;
    }
    printf("=== END DEBUG ===\n");
}

int main(void)
{
	char *input;
	t_list	*input_list;
	t_list	*current;
	t_input	*input_test;
	int i;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			exit(0);
		if (!input[0])
		{
			free(input);
			continue;
		}
		add_history(input);
		input_list = parse_line(input);
		if (!input_list)
		{
			printf("syntax error: unmatched quote\n");
			free(input);
			continue;
		}
		debug_print_input_list(input_list);
		input_test = (t_input *)input_list->content;
		if (input_test->argv && input_test->argv[0] && 
			(!strncmp(input_test->argv[0], "exit", 4) && input_test->argv[0][4] == '\0'))
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
	return 0;
}
