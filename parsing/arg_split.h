#ifndef ARG_SPLIT_H
# define ARG_SPLIT_H

# include "../minishellM.h"

char			**arg_split(char *s, int *inv_arg);
int				ft_cpy_alloc(char **arr, char *s);
unsigned int	count_args(char *s);
void			arg_len(char *s, int *i, int *len);
void			handle_dquote(char *s, int i, int *in_quote, int *in_word);
void			handle_quote(char *s, int i, int *in_quote, int *in_word);

#endif