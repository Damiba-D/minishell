/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hub2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:40 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:41 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(char **segments, t_list **input_list, t_list *new_node)
{
	if (segments)
		free_arr(segments);
	if (input_list && *input_list)
		ft_lstclear(input_list, free_input_node);
	if (new_node)
	{
		free_input_node(new_node->content);
		free(new_node);
	}
}
