
#include "minishellM.h"

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

int main(void)
{
    char *input;
    char **args;
    int inv_arg;
    int i;

    while (1)
    {
        input = readline("minishell: ");
        if (!input)
            exit(0);
        if (!input[0])
        {
            free(input);
            continue;
        }
        add_history(input);
        args = arg_split(input, &inv_arg);
        if (inv_arg == 2)
        {
            printf("syntax error: unmatched quote\n");
            free(input);
            continue;
        }
        if (!args || !args[0] || (!strncmp(args[0], "exit", 4) && args[0][4] == '\0'))
            exit(0);
        if (args[1])
        {
            i = 1;
            while (args[i])
            {
                printf("%s", args[i]);
                i++;
            }
            printf("\n");
        }
        free_arr(args);
        free(input);
    }
    return 0;
}
