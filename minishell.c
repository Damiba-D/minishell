
#include "minishellM.h"

void	free_input_list(t_input *input_list)
{
	t_input *current;
	t_input *next;

	current = input_list;
	while (current)
	{
		next = current->next;
		if (current->argv)
			free_arr(current->argv);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
		current = next;
	}
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

void	debug_print_input_list(t_input *input_list)
{
	t_input *current;
	int i;
	int cmd_num = 0;

	current = input_list;
	printf("=== DEBUG: Parsed Commands ===\n");
	while (current)
	{
		printf("Command %d:\n", cmd_num++);
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				printf("  argv[%d]: %s\n", i, current->argv[i]);
				i++;
			}
		}
		else
		{
			printf("  argv: NULL\n");
		}
		printf("  infile: %s\n", current->infile ? current->infile : "NULL");
		printf("  outfile: %s\n", current->outfile ? current->outfile : "NULL");
		printf("  append: %d\n", current->append);
		printf("  hdoc: %d\n", current->hdoc);
		printf("  next: %s\n", current->next ? "exists" : "NULL");
		printf("---\n");
		current = current->next;
	}
	printf("=== END DEBUG ===\n");
}

int main(void)
{
	char *input;
	t_input	*input_list;
	t_input	*current;
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
		if (input_list->argv && input_list->argv[0] && 
			(!strncmp(input_list->argv[0], "exit", 4) && input_list->argv[0][4] == '\0'))
		{
			free_input_list(input_list);
			free(input);
			exit(0);
		}
		current = input_list;
		while (current)
		{
			if (current->argv && current->argv[0])
			{
				i = 0;
				while (current->argv[i])
				{
					printf("%s", current->argv[i]);
					if (current->argv[i + 1])
						printf(" ");
					i++;
				}
				if (current->next)
					printf(" | ");
			}
			current = current->next;
		}
		printf("\n");
		
		free_input_list(input_list);
		free(input);
	}
	return 0;
}
