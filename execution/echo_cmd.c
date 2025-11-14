#include "minishellD.h"

void	echo_flag_handler(int *i, char **argv, int *nl_flag)
{
	int j;

	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 1;
		while (argv[*i][j] == 'n')
				j++;
		if (argv[*i][j] != '\0')
				return ;
		(*i)++;
		*nl_flag = 1;
	}
}

int	echo_cmd(char **argv)
{
	int i;
	int nl_flag;

	i = 1;
	nl_flag = 0;
	echo_flag_handler(&i, argv, &nl_flag);
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!nl_flag)
		printf("\n");
	return (0); 
}

