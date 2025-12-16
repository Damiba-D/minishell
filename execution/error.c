#include "../minishell.h"

/// @brief For printing any kind of error. If context & detail are NULL & err is set to false, nothing is printed
/// @param context what exactly failed, IE, malloc or a command such as cd
/// @param detail extra info as to what failed, IE, a file that could not be opened
/// @param err flag used to print exact error message if function sets errno upon failure
void print_err(char *context, char *detail, bool err)
{
	if (context || detail || err)
	{
		ft_putstr_fd("minishell: ", 2);
		if (context)
		{
			ft_putstr_fd(context, 2);
			ft_putstr_fd(": ", 2);
		}
		if (detail && err)
			perror(detail);
		else if (detail)
			ft_putendl_fd(detail, 2);
		else if (err)
			ft_putendl_fd(strerror(errno), 2);
	}
}