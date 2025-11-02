#include "minishellD.h"

/*
If delimiter is unquoted (double or single, does not matter), expansions are performed normally and \ must used to escape special characters
If any part of delimiter is quoted, everything appears to be treated a string literal
If delimeter is existing enviroment variable, it is not expanded but a newline is added at the beginning of output. Otherwise, no special behavior is noted.
 */