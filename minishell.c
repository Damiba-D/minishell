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
	init_env(&msh()->env);
	msh()->last_exit_status = 0;

	while (1)
	{
		msh()->cmdline = readline("minishell$ ");
		if (!msh()->cmdline)
			exit_cmd(NULL);
		if (!msh()->cmdline[0])
		{
			free(msh()->cmdline);
			continue ;
		}
		add_history(msh()->cmdline);
		msh()->inputlst = parse_line(msh()->cmdline);
		if (!msh()->inputlst)
		{
			free(msh()->inputlst);
			continue ;
		}
		executor();
	}
	return ((unsigned char)msh()->last_exit_status);
}
