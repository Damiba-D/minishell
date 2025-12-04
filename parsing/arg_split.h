#ifndef ARG_SPLIT_H
# define ARG_SPLIT_H

# include "parsing.h"

char			**arg_split(char *s, int *inv_arg);
int				ft_cpy_alloc(char **arr, char *s);
void			arg_len(char *s, int *i, int *len);

#endif