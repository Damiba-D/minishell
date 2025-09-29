#include "minishellM.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}