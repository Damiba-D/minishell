/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcardoso <mcardoso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:50:10 by mcardoso          #+#    #+#             */
/*   Updated: 2026/01/16 17:50:11 by mcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_SPLIT_H
# define ARG_SPLIT_H

# include "parsing.h"

char	**arg_split(char *s);
int		ft_cpy_alloc(char **arr, char *s);
void	arg_len(char *s, int *i, int *len);
int		has_unmatched_quote(char *s);

#endif