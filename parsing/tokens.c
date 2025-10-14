#include "../minishellM.h"

t_token *create_token(char *value, t_tokent type)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = ft_strdup(value);
    if (!new_token->value)
    {
        free(new_token);
        return (NULL);
    }
    new_token->type = type;
    new_token->next = NULL;
    return (new_token);
}

