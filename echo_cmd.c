#include "minishellD.h"

void	echo_flag_handler(int *i, char **argv, int *nl_flag)
{
	int j;
	int k;

	j = 0;
	k = *i;
	if (argv[k][j] != '-')
		return ;
	while (argv[k])
	{
		j = 0;
		if (argv[k][j] == '-' && argv[k][j + 1] == 'n')
		{
			j++;
			while (argv[k][j] == 'n')
				j++;
			if (argv[k][j] != '\0')
				return ;
		}
		k++;
	}
	*i = k;
	*nl_flag = 1;
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

