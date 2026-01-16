/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:47:19 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/16 17:47:20 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief For printing any kind of error. 
///If context & detail are NULL & err is set to false, nothing is printed
/// @param context what exactly failed, IE, malloc or a command such as cd
/// @param detail extra info as to what failed
/// IE, a file that could not be opened
/// @param err flag used to print exact error message
/// if function sets errno upon failure
void	print_err(char *context, char *detail, bool err)
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

void	print_hd_error(char *filename)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd("')", 2);
}
