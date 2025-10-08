/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:00:34 by ddamiba           #+#    #+#             */
/*   Updated: 2025/10/08 11:01:07 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char		*ptr;

	ptr = (char *)malloc(len * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, (char *)s1, len);
	return (ptr);
}