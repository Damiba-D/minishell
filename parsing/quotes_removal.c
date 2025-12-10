#include "../minishell.h"

static char *remove_quotes_str(char *str, int *in_sgl, int *in_dbl)
{
	int		i;
	int		j;
	char	*res;

	if(!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		update_quotes(str[i], &in_sgl, &in_dbl);
		if ((str[i] == '\'' && !in_dbl) || (str[i] == '\"' && !in_sgl))
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

void	remove_quotes_input(t_input *node)
{
	
}
