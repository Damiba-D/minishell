
#include "minishellD.h"

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell > ");
		if (!input || !input[0])
		{
			exit(1);
		}
		else
			add_history(input);
		if (!strncmp(input, "exit", 5))
		{
			exit(0);
		}
	}
	return 0;
}